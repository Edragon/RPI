
Using this routine requires first installing the library:
sudo apt-get install python-pip
sudo pip install python-can

Then make sure your mcp2515 kernel driver is open:
sudo vi /boot/config.txt

And add the following: 
dtparam=spi=on
dtoverlay=mcp2515-can0,oscillator=8000000,interrupt=25,spimaxfrequency=1000000

Then restart the raspberry pi：
sudo reboot

send run:
sudo python send.py

Receiving run:
sudo python receive.py

You will see the following:
Timestamp: 1527240783.548918        ID: 0123    S          DLC: 8    00 01 02 03 04 05 06 07
