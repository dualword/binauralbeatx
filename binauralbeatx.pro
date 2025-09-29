lessThan(QT_VERSION, 5.15) {
        error('Qt 5.15+ required...')
}

TEMPLATE = subdirs
SUBDIRS = src
