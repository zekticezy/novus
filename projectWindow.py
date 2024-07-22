# This file is a cruical part of Novus. It is used for the Project window you see when one of your .nvp files are active in the program. 
# Do not change anything here if you don't know what you're doing!
# - zekkie

import tkinter as tk
from tkinter import font as tkfont
from PIL import Image, ImageTk
import os

class DAWWindow(tk.Tk):
    def __init__(self):
        super().__init__()

        self.title("Novus (Development Build)")
        self.iconbitmap(os.path.join('cdn', 'img', 'icons', 'novusblack.ico'))
        self.state('zoomed')
        self.configure(bg='#828080')
        self.load_custom_font()
        self.initUI()

    def load_custom_font(self):
        font_path = os.path.join('cdn', 'font', 'Inter', 'Inter-VariableFont_slnt,wght.ttf')
        if os.path.exists(font_path):
            try:
                self.custom_font = tkfont.Font(family="Inter", size=9, weight="bold")
            except tk.TclError:
                print("Failed to load custom font.")

    def initUI(self):
        self.canvas = tk.Canvas(self, bg='#828080', bd=0, highlightthickness=0)
        self.canvas.pack(fill=tk.BOTH, expand=True)

        self.add_square(15, 67, 272, 940, '#A5A5A5')
        self.add_square(294, 67, 272, 940, '#A5A5A5')
        self.add_square(15, 34, 552, 33, '#BFBFBF', "Explorer", 13, 15, 76)

        self.create_label("Quick Access", 72.8)
        self.create_test_button("Most Used", 94, os.path.join('cdn', 'img', 'icons', 'Explorer', 'mostused.png'))
        self.create_test_button("Favorites", 115, os.path.join('cdn', 'img', 'icons', 'Explorer', 'favorites.png'))
        self.create_test_button("Recent Files", 136, os.path.join('cdn', 'img', 'icons', 'Explorer', 'recentfiles.png'))

        self.create_label("Library", 157)

        library_buttons = [
            ("Sounds", "sounds.png"),
            ("Instruments", "instruments.png"),
            ("Effects", "effects.png"),
            ("MIDI", "MIDI.png"),
            ("Synths", "synths.png"),
            ("Plug-ins", "plugins.png"),
            ("Presets", "presets.png"),
            ("Audio Recordings", "audiorecordings.png"),
            ("Projects", "projects.png")
        ]

        y_position = 178
        button_height = 18
        for text, icon_file in library_buttons:
            icon_path = os.path.join('cdn', 'img', 'icons', 'Explorer', icon_file)
            self.create_test_button(text, y_position, icon_path)
            y_position += button_height + 3.5

    def create_label(self, text, y_position):
        label = tk.Label(self.canvas, text=text, font=self.custom_font, bg='#A5A5A5', fg='#7D7D7D')
        label.place(x=15, y=y_position, anchor='nw')

    def create_test_button(self, text, y_position, icon_path):
        custom_font = self.custom_font
        button = tk.Button(self.canvas, text=text, font=custom_font, bg='#A5A5A5', fg='#FFFFFF', anchor='w', padx=10, bd=0)
        button.place(x=15, y=y_position, width=272, height=18)
        button.bind("<Enter>", lambda e: button.configure(bg='#748790'))
        button.bind("<Leave>", lambda e: button.configure(bg='#A5A5A5'))
        button.bind("<Button-1>", lambda e: button.configure(bg='#BABABA'))
        icon_size = (16, 16)
        self.set_button_icon(button, icon_path, icon_size)
        button.lift()

    def set_button_icon(self, button, icon_path, size):
        try:
            image = Image.open(icon_path)
            image = image.resize(size, Image.LANCZOS)
            photo = ImageTk.PhotoImage(image)
            button.config(image=photo, compound='left')
            button.image = photo
        except Exception as e:
            print(f"Error loading icon: {e}")

    def add_square(self, x, y, width, height, color, text=None, text_size=None, text_x=None, text_y=None):
        frame = tk.Frame(self.canvas, bg=color, width=width, height=height)
        frame.place(x=x, y=y)
        self.canvas.create_window((x, y), window=frame, anchor='nw')

        if text:
            custom_font = tkfont.Font(family="Inter", size=text_size, weight="bold")
            label = tk.Label(frame, text=text, font=custom_font, bg=color, anchor='w')
            label.place(x=text_x, y=text_y)
            label.configure(fg='#4D4D4D')

            if text == "Explorer":
                explorer_label = tk.Label(frame, text="Explorer", font=tkfont.Font(family="Inter", size=13, weight="bold"), bg=color, fg='#4D4D4D')
                explorer_label.place(x=10, y=5)

if __name__ == '__main__':
    app = DAWWindow()
    app.mainloop()
