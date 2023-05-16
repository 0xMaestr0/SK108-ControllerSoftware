# SK108 Controller

This was supposed to be a control center for SK108 and related boards. I wanted to contribute to the open-source community for once in years. 

I deobfuscated the original drivers and shortly after managed to interact with the board. I started experimenting with built-in lighting modes, and I was playing around with the speed parameter, trying out the fastest one. After it was done, I turned off backlight mode and then my keyboard stopped sending input to the computer, which happened before while writing the driver and experimenting with random settings, so I simply reset it by holding FN+ESC for 5 seconds which fixed the issue, but as I ran my driver again it didn't work as expected, and then shortly after my keyboard completely died and stopped showing up in the devices list.

Their official control center doesn't work properly and it crashes a lot. If it doesn't detect your device, it is because their center software uses hardcoded product IDs which may change from board to board, which is why it fails to detect your board.
