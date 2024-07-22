import tkinter as tk
from tkinter import font as tkfont
from PIL import Image, ImageTk
import os

class DAWWindow(tk.Tk):
    def __init__(self):
        super().__init__()

        # Set window title and icon
        self.title("Novus (Development Build)")
        self.iconbitmap(os.path.join('cdn', 'img', 'icons', 'novusblack.ico'))

        # Set window to be maximized by default
        self.state('zoomed')

        # Configure background
        self.configure(bg='#828080')

        # Load custom font
        self.load_custom_font()

        # Initialize UI
        self.initUI()

    def load_custom_font(self):
        # Load the custom font
        font_path = os.path.join('cdn', 'font', 'Inter', 'Inter-VariableFont_slnt,wght.ttf')
        if os.path.exists(font_path):
            try:
                # Register the font with Tkinter
                self.tk.call("font", "create", "Inter", "-family", "Inter", "-size", "9", "-weight", "bold")
            except tk.TclError:
                print("Failed to load custom font.")

    def initUI(self):
        # Create a canvas for layering
        self.canvas = tk.Canvas(self, bg='#828080', bd=0, highlightthickness=0)
        self.canvas.pack(fill=tk.BOTH, expand=True)

        # Add squares
        self.add_square(15, 67, 272, 940, '#A5A5A5')
        self.add_square(294, 67, 272, 940, '#A5A5A5')
        self.add_square(15, 34, 552, 33, '#BFBFBF', "Explorer", 13, 15, 76)

        # Add a simple test button with the same size and position as "Most Used"
        self.create_test_button()

    def add_square(self, x, y, width, height, color, text=None, text_size=None, text_x=None, text_y=None):
        # Create a frame as a child of the canvas
        frame = tk.Frame(self.canvas, bg=color, width=width, height=height)
        frame.place(x=x, y=y)

        # Create a canvas item for the frame
        self.canvas.create_window((x, y), window=frame, anchor='nw')

        if text:
            # Use the custom Inter font
            custom_font = tkfont.Font(family="Inter", size=text_size, weight="bold")
            label = tk.Label(frame, text=text, font=custom_font, bg=color, anchor='w')
            label.place(x=text_x, y=text_y)
            label.configure(fg='#4D4D4D')

    def create_test_button(self):
        # Set the padding offset
        offset = 10  # Updated offset value

        # Create a test button with the same position and size as "Most Used"
        custom_font = tkfont.Font(family="Inter", size=9, weight="bold")
        test_button = tk.Button(self.canvas, text="Most Used", bg='#A5A5A5', fg='#FFFFFF', font=custom_font, anchor='w', padx=offset, bd=0)
        test_button.place(x=15, y=94, width=272, height=18)

        # Add bindings to change background color on hover and click
        test_button.bind("<Enter>", lambda e: test_button.configure(bg='#748790'))
        test_button.bind("<Leave>", lambda e: test_button.configure(bg='#A5A5A5'))
        test_button.bind("<Button-1>", lambda e: test_button.configure(bg='#BABABA'))

        # Load and set the icon
        icon_path = os.path.join('cdn', 'img', 'icons', 'Explorer', 'mostused.png')
        icon_size = (16, 16)  # Set your desired icon size here
        self.set_button_icon(test_button, icon_path, icon_size)

        # Ensure the button is above other widgets
        test_button.lift()

    def set_button_icon(self, button, icon_path, size):
        # Load and resize the icon image
        try:
            image = Image.open(icon_path)
            image = image.resize(size, Image.Resampling.LANCZOS)  # Use LANCZOS for better quality
            photo = ImageTk.PhotoImage(image)

            # Set the icon image for the button
            button.config(image=photo, compound='left')
            button.image = photo  # Keep a reference to prevent garbage collection
        except Exception as e:
            print(f"Error loading icon: {e}")

if __name__ == '__main__':
    app = DAWWindow()
    app.mainloop()
