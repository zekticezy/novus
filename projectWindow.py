import tkinter as tk
from tkinter import font as tkfont
from PIL import Image, ImageTk
import os
import shutil
import subprocess
import tkinter.simpledialog as simpledialog  # Import this for simpledialog

class DAWWindow(tk.Tk):
    def __init__(self):
        super().__init__()

        self.title("Novus (Development Build)")
        self.iconbitmap(os.path.join('cdn', 'img', 'icons', 'novusblack.ico'))
        self.state('zoomed')
        self.configure(bg='#828080')

        self.load_custom_font()
        self.initUI()

        # Copy folder on launch
        self.copy_folders_to_documents()

        # Folder path mapping
        self.folder_mapping = {
            "Sounds": "Sounds",
            "Instruments": "Instruments",
            "Effects": "Effects",
            "MIDI": "MIDI",
            "Synths": "Synths",
            "Plug-ins": "Plug-ins",
            "Presets": "Presets",
            "Audio Recordings": "Audio Recordings",
            "Projects": "Projects"
        }
    
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
            button = self.create_test_button(text, y_position, icon_path)
            y_position += button_height + 3.5
            button.config(command=lambda t=text: self.display_files(t))

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
        return button

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

    def display_files(self, folder_name):
        file_explorer_x = 294
        file_explorer_y = 67
        file_explorer_width = 272
        file_explorer_height = 940

        # Clear previous files in the file explorer
        for widget in self.canvas.winfo_children():
            if widget.winfo_x() >= file_explorer_x:
                widget.destroy()

        # Ensure the file explorer area remains fixed in size
        self.canvas.create_rectangle(file_explorer_x, file_explorer_y, file_explorer_x + file_explorer_width, file_explorer_y + file_explorer_height, fill='#A5A5A5', outline='')

        folder_path = os.path.join('App Preferences', 'Explorer', 'Explorer Folders', self.folder_mapping.get(folder_name, ''))
        if not os.path.exists(folder_path):
            return

        files = os.listdir(folder_path)
        y_position = file_explorer_y

        # Define audio file extensions
        audio_extensions = ('.mp3', '.m4a', '.wav', '.flac', '.aac', '.wma', '.mp4', '.aiff')

        for file in files:
            file_path = os.path.join(folder_path, file)
            # Determine icon based on file extension
            if file.lower().endswith(audio_extensions):
                icon_path = os.path.join('cdn', 'img', 'icons', 'Explorer', 'audiofile.png')
            else:
                icon_path = None

            # Create label for file
            label = tk.Label(self.canvas, text=file, font=self.custom_font, bg='#A5A5A5', fg='#FFFFFF')
            label.place(x=file_explorer_x, y=y_position, anchor='nw')
            label.bind("<Button-3>", lambda e, p=file_path: self.show_context_menu(e, p))
            y_position += 18

            # Add icon if available
            if icon_path:
                self.set_button_icon(label, icon_path, (16, 16))

    def set_file_icon(self, label, icon_path, size):
        try:
            image = Image.open(icon_path)
            image = image.resize(size, Image.LANCZOS)
            photo = ImageTk.PhotoImage(image)
            label.config(image=photo)
            label.image = photo
        except Exception as e:
            print(f"Error loading icon: {e}")

    def show_context_menu(self, event, file_path):
        context_menu = tk.Menu(self, tearoff=0)
        context_menu.add_command(label="Open in Windows Explorer", command=lambda: self.open_in_windows_explorer(file_path))
        context_menu.add_command(label="Rename", command=lambda: self.rename_file(file_path))
        context_menu.add_command(label="Delete", command=lambda: self.delete_file(file_path))
        context_menu.post(event.x_root, event.y_root)

    def open_in_windows_explorer(self, file_path):
        # Get the directory containing the file
        folder_path = os.path.dirname(file_path)
        if os.name == 'nt':
            subprocess.run(['explorer', folder_path])
        elif os.name == 'posix':
            # For Unix-based systems, you might use a different method, e.g., `xdg-open`
            subprocess.run(['xdg-open', folder_path])

    def rename_file(self, file_path):
        new_name = simpledialog.askstring("Rename File", "Enter the new name:")
        if new_name:
            try:
                new_path = os.path.join(os.path.dirname(file_path), new_name)
                os.rename(file_path, new_path)
                self.display_files(os.path.basename(os.path.dirname(file_path)))
            except Exception as e:
                print(f"Error renaming file: {e}")

    def delete_file(self, file_path):
        if simpledialog.askyesno("Delete File", "Are you sure you want to delete this file?"):
            os.remove(file_path)
            self.display_files(os.path.basename(os.path.dirname(file_path)))

    def copy_folders_to_documents(self):
        source_folder = os.path.join('App Preferences', 'Explorer', 'Explorer Folders')
        documents_folder = os.path.expanduser("~/Documents/Novus")

        if os.path.exists(source_folder):
            if not os.path.exists(documents_folder):
                os.makedirs(documents_folder)
            for folder in os.listdir(source_folder):
                src_path = os.path.join(source_folder, folder)
                dest_path = os.path.join(documents_folder, folder)
                if os.path.isdir(src_path):
                    shutil.copytree(src_path, dest_path, dirs_exist_ok=True)
        else:
            print(f"Source folder '{source_folder}' does not exist.")

if __name__ == "__main__":
    app = DAWWindow()
    app.mainloop()
