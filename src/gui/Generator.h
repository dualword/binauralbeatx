/*
 * Copyright (C) 2025 Alexander Busorgin
 * This file is part of BinauralBeatX (https://github.com/dualword/binauralbeatx)
 * License: GPL-3 (GPL-3.0-only)
 *
 * BinauralBeatX is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * BinauralBeatX is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with BinauralBeatX.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef GENERATOR_H
#define GENERATOR_H

#include <QtWidgets>
#include <QAudioOutput>
#include <QRandomGenerator>

class Generator : public QIODevice {
    Q_OBJECT

public:
    Generator(qreal f1, qreal f2) : m_freq1(f1), m_freq2(f2) {
        m_format.setSampleRate(44100);
        m_format.setChannelCount(2);
        m_format.setSampleSize(16);
        m_format.setByteOrder(QAudioFormat::LittleEndian);
        m_format.setSampleType(QAudioFormat::SignedInt);
        m_out.reset(new QAudioOutput(m_format, this));
        connect(m_out.get(), SIGNAL(notify()), SLOT(notified()));
        connect(m_out.get(), SIGNAL(stateChanged(QAudio::State)), SLOT(stateChanged(QAudio::State)));
    }
    virtual ~Generator() {}
    void noise(int val){m_noise = val;}

    void start() {
        generateData();
        open(QIODevice::ReadOnly);
        m_out->start(this);
    }

    void stop() {
        m_pos = 0;
        close();
        m_out->stop();
    }

    QAudioOutput* output() { return m_out.get(); }

signals:
    void setBuffer(const QByteArray&, qint64);

protected:
    qint64 readData(char *data, qint64 len) override {
        qint64 total = 0;
        if (!m_buf.isEmpty()) {
            while (total < len) {
                const qint64 chunk = qMin((m_buf.size() - m_pos), len - total);
                memcpy(data + total, m_buf.constData() + m_pos, chunk);
                if( (m_pos += chunk) >= m_buf.size()) m_pos = 0;
                total += chunk;
            }
        }
        return total;
    }

    qint64 writeData(const char *, qint64) override { return 0; }
    qint64 bytesAvailable() const override { return m_buf.size() + QIODevice::bytesAvailable(); }

private slots:
    void stateChanged(QAudio::State state) {}
    void notified() {}

private:
    void generateData() {
        const int channelBytes = m_format.sampleSize() / 8;
        const int duration = 1000000;
        qint64 len = (m_format.sampleRate() * m_format.channelCount() * (m_format.sampleSize() / 8) * duration) / 1000000;
        m_buf.resize(len);
        unsigned char *ptr = reinterpret_cast<unsigned char *>(m_buf.data());
        std::uniform_real_distribution<> dist(-0.25, 0.25);

        int sampleIndex = 0;
        int j = 0;
        while (len) {
            qreal x1, x2;
            if (j % 2 == 0) {
                x1 = qSin(2 * M_PI * m_freq1 * qreal(sampleIndex % m_format.sampleRate()) / m_format.sampleRate());
               if(m_noise) x1 = (x1 * 0.9  + dist(*QRandomGenerator::global()) * 0.1 );
            } else {
                x2 = qSin(2 * M_PI * m_freq2 * qreal(sampleIndex % m_format.sampleRate()) / m_format.sampleRate());
                if(m_noise) x2 = (x2 * 0.9  + dist(*QRandomGenerator::global()) * 0.1 );
            }

            for (int i = 0; i < m_format.channelCount(); ++i) {
                if (i % 2 == 0) {
                    *reinterpret_cast<qint16 *>(ptr) = static_cast<qint16>(x1 * 32767);
                } else {
                    *reinterpret_cast<qint16 *>(ptr) = static_cast<qint16>(x2 * 32767);
                }
                ptr += channelBytes;
                len -= channelBytes;
            }
            ++sampleIndex;
            j++;
        }
    }

    QRandomGenerator *rnd = QRandomGenerator::global();
    QAudioFormat m_format;
    QScopedPointer<QAudioOutput> m_out;
    QByteArray m_buf;
    qint64 m_pos = 0;
    qreal m_freq1, m_freq2;
    bool m_noise = false;

};

#endif // GENERATOR_H
