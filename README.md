# cc-port-scanner
A simple port scanner based on the codechallenges.fyi challenge. 

## Step 1: 
- Create a simple CLI program that accepts two arguments: a host and a port.
- Attempt to open a full TCP connection to that port. Report status of connection.
- For this step, I tested it by opening one connection to scanme.nmap.org (45.33.32.156) on port 80 (HTTP).
- Error handling for command line arguments, specifically the port number.

## Step 2:
- Implemented a vanilla scan: scan all ports 1-65535. Tested on a local python web server running on my desktop.
- Takes ages.