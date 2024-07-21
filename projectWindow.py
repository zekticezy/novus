import sys
from PyQt5.QtWidgets import QApplication, QWidget, QFrame, QLabel, QPushButton, QVBoxLayout, QHBoxLayout, QSlider
from PyQt5.QtGui import QFont, QPixmap, QIcon
from PyQt5.QtCore import Qt

# Import the necessary libraries for your DAW
import pydub
import numpy as np
import scipy
import sounddevice as sd
import librosa

class DAWWindow(QWidget):
    def __init__(self):
        super().__init__()
        self.initUI()
        self.activeBox = None  # To keep track of the currently active box

    def initUI(self):
        # Set the reference resolution
        ref_width = 1920
        ref_height = 1080

        # Maximize the window by default
        self.setWindowState(Qt.WindowMaximized)
        
        # Set the background color
        self.setStyleSheet("background-color: #373737;")

        # Set the application icon
        self.setWindowIcon(QIcon('img/icons/novusblack.ico'))
        
        # Set the application name (title bar and taskbar)
        self.setWindowTitle('Novus')
        
        # Add the top box
        top_box = QFrame(self)
        top_box.setStyleSheet("background-color: #555555;")
        top_box.setGeometry(int(15 * ref_width / ref_width), int(34 * ref_height / ref_height), int(552 * ref_width / ref_width), int(33.13 * ref_height / ref_height))

        # Add text to the top box
        explorer_label = QLabel('Explorer', self)
        explorer_label.setGeometry(int(32 * ref_width / ref_width), int(34 * ref_height / ref_height), 200, 30)
        explorer_label.setStyleSheet("color: white;")
        font = QFont()
        font.setPointSize(13)
        explorer_label.setFont(font)

        # Add the vertical boxes
        box1 = QFrame(self)
        box1.setStyleSheet("background-color: #414141;")
        box1.setGeometry(int(15 * ref_width / ref_width), int(67 * ref_height / ref_height), int(272 * ref_width / ref_width), int(940 * ref_height / ref_height))
        
        # Add label and text for "Categories"
        categories_label = QLabel('Categories', self)
        categories_label.setGeometry(int(22 * ref_width / ref_width), int(78 * ref_height / ref_height), 200, 30)
        categories_label.setStyleSheet("color: white;")
        categories_font = QFont()
        categories_font.setPointSize(10)
        categories_font.setBold(True)
        categories_label.setFont(categories_font)

        # Add "Quick Access" text
        quick_access_label = QLabel('Quick Access', self)
        quick_access_label.setGeometry(int(22 * ref_width / ref_width), int(108 * ref_height / ref_height), 200, 30)
        quick_access_label.setStyleSheet("color: #7D7D7D;")
        quick_access_font = QFont()
        quick_access_font.setPointSize(10)
        quick_access_font.setBold(True)
        quick_access_label.setFont(quick_access_font)

        # Add "Sounds" section
        image_label = QLabel(self)
        image_label.setGeometry(int(22 * ref_width / ref_width), int(138 * ref_height / ref_height), int(13 * ref_width / ref_width), int(13 * ref_height / ref_height))
        empty_pixmap = QPixmap(int(13 * ref_width / ref_width), int(13 * ref_height / ref_height))
        empty_pixmap.fill(Qt.transparent)
        image_label.setPixmap(empty_pixmap)

        sounds_label = QLabel('Sounds', self)
        sounds_label.setGeometry(int(43 * ref_width / ref_width), int(138 * ref_height / ref_height), 100, 30)
        sounds_label.setStyleSheet("color: #CBCBCB;")
        sounds_font = QFont()
        sounds_font.setPointSize(9)
        sounds_font.setWeight(QFont.DemiBold)
        sounds_label.setFont(sounds_font)

        # Create interactive boxes
        self.createInteractiveBox(int(22 * ref_width / ref_width), int(167 * ref_height / ref_height), 'Sounds')
        self.createInteractiveBox(int(22 * ref_width / ref_width), int(185 * ref_height / ref_height), 'Effects')
        self.createInteractiveBox(int(22 * ref_width / ref_width), int(203 * ref_height / ref_height), 'Presets')
        self.createInteractiveBox(int(22 * ref_width / ref_width), int(221 * ref_height / ref_height), 'MIDI Patterns')
        self.createInteractiveBox(int(22 * ref_width / ref_width), int(239 * ref_height / ref_height), 'Plug-ins')

        # Add the timeline/playlist box
        timeline_box = QFrame(self)
        timeline_box.setStyleSheet("background-color: #414141;")
        timeline_box.setGeometry(int(586 * ref_width / ref_width), int(34 * ref_height / ref_height), int(1299 * ref_width / ref_width), int(973 * ref_height / ref_height))

        # Add controls to the timeline box
        self.addTimelineControls(timeline_box)
        
        # Show the window
        self.show()

    def createInteractiveBox(self, x, y, text):
        box = QFrame(self)
        box.setStyleSheet("background-color: transparent; border: none;")
        box.setGeometry(x, y, int(155 * 1920 / 1920), int(18 * 1080 / 1080))
        box.setCursor(Qt.PointingHandCursor)
        box.mousePressEvent = lambda event, box=box, text=text: self.onBoxClicked(box, text)

        # Add label for the text
        label = QLabel(text, self)
        label.setGeometry(x + 22, y, 150, 18)  # Adjust x for padding
        label.setStyleSheet("color: #CBCBCB;")  # Default text color
        label_font = QFont()
        label_font.setPointSize(9)
        label_font.setWeight(QFont.DemiBold)
        label.setFont(label_font)
        label.setObjectName(f'{text}_label')

    def onBoxClicked(self, box, text):
        # Reset color of the previously active box
        if self.activeBox is not None:
            self.activeBox.setStyleSheet("background-color: transparent; border: none;")
        
        # Set the clicked box to active
        box.setStyleSheet("background-color: #748790; border: none;")
        self.activeBox = box

        # Update label colors
        for label in self.findChildren(QLabel):
            if label.objectName() == f'{text}_label':
                label.setStyleSheet("color: white;")
            else:
                label.setStyleSheet("color: #CBCBCB;")

    def addTimelineControls(self, timeline_box):
        # Create a horizontal layout for the controls
        controls_layout = QHBoxLayout()
        controls_layout.setContentsMargins(0, 0, 0, 0)
        controls_layout.setSpacing(10)  # Optional: Adjust spacing between buttons

        # Define empty image size
        button_size = 34
        empty_pixmap = QPixmap(button_size, button_size)
        empty_pixmap.fill(Qt.transparent)

        # Create and style Play button with empty image
        play_button = QPushButton(self)
        play_button.setIcon(QIcon(empty_pixmap))
        play_button.setIconSize(empty_pixmap.size())
        play_button.setGeometry(int(909 * 1920 / 1920), int(0 * 1080 / 1080), int(button_size * 1920 / 1920), int(button_size * 1080 / 1080))
        play_button.setStyleSheet("background-color: #555555;")
        controls_layout.addWidget(play_button)

        # Create and style Pause button with empty image
        pause_button = QPushButton(self)
        pause_button.setIcon(QIcon(empty_pixmap))
        pause_button.setIconSize(empty_pixmap.size())
        pause_button.setGeometry(int(943 * 1920 / 1920), int(0 * 1080 / 1080), int(button_size * 1920 / 1920), int(button_size * 1080 / 1080))
        pause_button.setStyleSheet("background-color: #555555;")
        controls_layout.addWidget(pause_button)

        # Create and style Stop button with empty image
        stop_button = QPushButton(self)
        stop_button.setIcon(QIcon(empty_pixmap))
        stop_button.setIconSize(empty_pixmap.size())
        stop_button.setGeometry(int(977 * 1920 / 1920), int(0 * 1080 / 1080), int(button_size * 1920 / 1920), int(button_size * 1080 / 1080))
        stop_button.setStyleSheet("background-color: #555555;")
        controls_layout.addWidget(stop_button)

        # Create and style Progress bar
        progress_bar = QSlider(Qt.Horizontal, self)
        progress_bar.setStyleSheet("QSlider::groove:horizontal {background: #555555;} QSlider::handle:horizontal {background: #748790;}")
        controls_layout.addWidget(progress_bar)

        # Add controls layout to the timeline box
        controls_box = QFrame(self)
        controls_box.setStyleSheet("background-color: transparent;")
        controls_box.setLayout(controls_layout)
        controls_box.setGeometry(int(586 * 1920 / 1920), int(34 * 1080 / 1080), int(1299 * 1920 / 1920), int(34 * 1080 / 1080))  # Adjust as needed

if __name__ == '__main__':
    app = QApplication(sys.argv)
    daw = DAWWindow()
    sys.exit(app.exec_())
