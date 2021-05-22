# TimeSync

TimeSync is a time synchronization program for Windows. Time is taken from one of the two Polish NTP servers.

The program uses the [QNtp](https://github.com/elrinor/qntp) library to retrieve time from the server.

## How To Use

1. Run the program as administrator. This is needed to change the time in the system.
2. Right click on the icon in the system tray.
3. Select the IP of one of the NTP servers.
4. An appropriate message will be displayed when synchronization is complete.

# License

TimeSync is licensed under MIT. The QNtp library is GNU General Public License 3.0