Hi, I have uploaded an STM32CubeIDE project using TinyUSB to my GitHub repo.  
The project runs fine, but for anyone who wants to try it, here’s how to run:

1. Clone the repository:

2. Open the project in **STM32CubeIDE**.

3. Exclude these folders from the build:
- `tinyusb/hw`
- `tinyusb/examples`

(Right-click folder → Resource Configurations → Exclude from Build → Select Debug & Release)

4. Build and flash to your STM32 board.

STM32CubeIDE project is uploaded without `.gitignore`, so all required files are included.

Thanks!
