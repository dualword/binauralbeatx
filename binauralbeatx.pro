lessThan(QT_VERSION, 6.8) {
        error('Qt 6.8+ required...')
}

TEMPLATE = subdirs
SUBDIRS = src
