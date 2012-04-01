#-----------------------
# C++11
#-----------------------
QMAKE_CXXFLAGS += -std=gnu++0x
#QMAKE_CXXFLAGS += -std=c++0x
#QMAKE_CXXFLAGS += -U__STRICT_ANSI__

SOURCES += mainwindow.cpp \
            ONode.cpp \
            Node.cpp \
            INode.cpp \
            CellView.cpp \
            Cell.cpp \
            AndCellProcessStrategy.cpp \
            OrCellProcessStrategy.cpp \
            CellCreator.cpp \
            TextEditLogger.cpp \
            Logger.cpp \
            AboutDialog.cpp \
            IBusCellProcessStrategy.cpp \
            CellProcessStrategy.cpp \
            CellSizeDialog.cpp \
            ConnectorView.cpp \
            CellConnectionDialog.cpp \
            NotCellProcessStrategy.cpp \
            OBusCellProcessStrategy.cpp

HEADERS  += mainwindow.h \
			ONode.h \
            Node.h \
            INode.h \
            CellView.h \
            Cell.h \
            Bus.h \
            CellProcessStrategy.h \
            AndCellProcessStrategy.h \
            OrCellProcessStrategy.h \
            CellCreator.h \
            Logger.h \
            TextEditLogger.h \
            AboutDialog.h \
            IBusCellProcessStrategy.h \
            CellSizeDialog.h \
            ConnectorView.h \
            CellConnectionDialog.h \
            NotCellProcessStrategy.h \
            OBusCellProcessStrategy.h

FORMS    += mainwindow.ui \
            AboutDialog.ui \
            CellSizeDialog.ui \
            CellConnectionDialog.ui

RESOURCES += resources.qrc
