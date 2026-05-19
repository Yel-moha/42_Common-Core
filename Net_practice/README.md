*This project has been created as part of the 42 curriculum by yel-moha.*

# NetPractice

## Description
NetPractice is a 42 networking exercise focused on understanding how small TCP/IP networks work. The goal is to configure simulated network topologies so that hosts can communicate correctly by setting IP addresses, subnet masks, gateways, and routes.

The project contains 10 levels of increasing difficulty. Each level presents an incomplete network diagram and a set of objectives. You must complete the configuration until the network becomes valid.

## Instructions
1. Download and extract the project files.
2. Open the `net_practice.1.9/net_practice/` folder.
3. Run `./run.sh` to start the local web server and open the training interface.
4. If `run.sh` does not work, start a local server manually with `python3 -m http.server 49242` and open `http://localhost:49242` in your browser.
5. Enter your login to use your personal configuration, or use the evaluation tab for a random one.
6. Solve each level by filling the unshaded fields, then use `Check again` to validate your configuration.
7. When a level is solved, use `Get my config` to export the configuration before moving to the next one.

## Submission
To submit the project, place the 10 exported configuration files, one per level, at the repository root.

## Resources
Useful topics to study for this project:

- TCP/IP addressing and IPv4 basics
- Subnet masks and CIDR notation
- Default gateways
- Routers and switches
- Routing tables

References that may help:

- Basicly peer to peer method
- RFC 950: Internet Standard Subnetting Procedure
- RFC 1918: Address Allocation for Private Internets
- General IPv4 and subnetting documentation
- Router, switch, and OSI layer learning resources
