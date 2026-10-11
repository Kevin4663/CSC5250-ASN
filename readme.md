# projects-uvm

Network systems assignments. Code is written on Windows and built and run on two Ubuntu VMs.

## Layout

- assignment1/ - TCP client and server
- assignment2/ - hostname lookup with gethostbyname()
- zips/ - zipped submissions

## Ubuntu VMs

- Server VM: runs the server program. Start it first.
- Client VM: runs the client program and connects to the server VM.

Both VMs need the build tools:

```bash
sudo apt update
sudo apt install build-essential
```

Find the server VM's IP address (run on the server VM):

```bash
ip addr
hostname -I
```

Check that the client can reach the server (run on the client VM):

```bash
ping <server-ip>
```

If a firewall blocks the port (run on the server VM):

```bash
sudo ufw allow <port>/tcp
```

## Getting the code onto a VM

```bash
git clone https://github.com/Kevin4663/projects-uvm.git
cd projects-uvm
git pull
```

Or copy files from Windows with scp:

```bash
scp -r assignment1 <user>@<vm-ip>:~/
```

## Build and run

```bash
cd assignment2
make
./getaddr www.google.com
make clean
```

For assignment1, build and run the server on the server VM, then the client on the client VM, using the server IP and port.

## Zip a submission

Run these from the repo root. Run `make clean` first so no binaries are included.

PowerShell on Windows:

```powershell
Compress-Archive -Path .\assignment2 -DestinationPath .\zips\assignment2.zip -Force
```

Ubuntu:

```bash
zip -r zips/assignment2.zip assignment2
```

Check the contents of a zip:

```bash
unzip -l zips/assignment2.zip
```

## Git

```bash
git status
git add .
git commit -m "message"
git push
```
