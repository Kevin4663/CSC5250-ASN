========================================================================
Network Systems Assignment: Hostname Resolution Using gethostbyname()
========================================================================

1. Description
--------------
This program takes a machine name (hostname) as a command-line argument,
resolves it using the POSIX gethostbyname() system routine, and reports:
  - Total lookup execution time in milliseconds
  - The official host name
  - All configured aliases (CNAMEs)
  - All resolved IPv4 addresses in dotted-decimal format

If an invalid hostname or network error occurs, appropriate error messages
are printed to stderr via herror().

2. Files Included
-----------------
  - getaddr.c   : Source code implementation
  - Makefile    : Build automation file using gcc
  - readme.txt  : Project documentation and execution instructions

3. Compilation Instructions
---------------------------
To compile the program, run:
    make

To remove compiled binaries prior to archiving:
    make clean

4. Execution Instructions
-------------------------
Run the binary with a valid hostname:
    ./getaddr <hostname>

Examples:
    ./getaddr www.bestbuy.com
    ./getaddr google.com
    ./getaddr invalid.test.hostname

5. Sample Output
----------------
$ ./getaddr www.bestbuy.com
execution time: 14.215 milliseconds
Official name: e10776.g.akamaiedge.net
Aliases: www.bestbuy.com, wildcard.bestbuy.com.edgekey.net
Addresses: 23.217.138.110, 23.217.138.108

6. Notes / Limitations
----------------------
- gethostbyname() only supports IPv4 (AF_INET) resolution.
- Ensure hostnames do not contain protocol prefixes (e.g., use
  "www.bestbuy.com" rather than "https://www.bestbuy.com/").
