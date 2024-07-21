import sys
from PyQt5.QtWidgets import QApplication, QWidget, QDesktopWidget

import pydub
import numpy as np
import scipy
import sounddevice as sd
import librosa

class DAWWindow(QWidget):
    def __init__(self):
        super().__init__()
        self.initUI()

    def initUI(self):
        screen = QDesktopWidget().screenGeometry()
        self.setGeometry(0, 0, screen.width(), screen.height())
        self.setStyleSheet("background-color: #141414;")

if __name__ == '__main__':
    app = QApplication(sys.argv)
    daw = DAWWindow()
    daw.show()
    sys.exit(app.exec_())
