# How to set up Almalinux 9 on Windows 11 using Docker
In this guide we are going to learn step by step how to set up an **Almalinux9** environment on a **Windows 11** OS using **Docker**. 
## What is Almalinux9 ?
Almalinux9 is a linux distro that is the direct successor of **Red Hat Enterprise Linux 9 (RHEL9)**. AlmaLinux provides a stable, production-ready environment with long-term support and security updates.
## What is Docker ?
Docker is an open-source platform that enables developers to build, package, and run applications in lightweight, portable containers. These containers include everything needed to run an application—code, runtime, libraries, and dependencies—ensuring consistency across different environments. Docker simplifies software deployment, improves scalability, and allows applications to run reliably on any system, whether it's a developer’s laptop, a test server, or a cloud platform.
## Install Docker
First navigate to the **docker.com** website. On the homepage click on the **Download Docker** button and select **Download for Windows-AMD64**.

![](https://github.com/DanieleDemeneghi/scientific_computing_phd_physics/blob/main/scps_1.png)

Once downloaded open the executable file and click on the **Install** button. After this step close the configurator and restart your PC. Open the Docker Desktop application and accept the license agreement.
## Install Almalinux9 on Docker
Open the Docker Desktop application and select the Terminal

![](https://github.com/DanieleDemeneghi/scientific_computing_phd_physics/blob/main/scps_2.png)

1. In the terminal insert the following command to get the image of almalinux9

   `docker pull almalinux:9`.
   
2. The image is now present in the **Images** section of Docker. To package the image in a container insert the following command in the terminal

   `docker run -it --name my_container_name almalinux:9 /bin/bash`.
   
   This command assigns the name *my_container_name* to the container of almalinux9 and runs it. Now, we have an almalinux9 environment inside the Terminal.
3. To exit the container insert the command
   
   `exit`.
   
4. To start the container insert the command

   `docker start -i my_container_name `.

## Conclusion
You can now access the almalinux9 environment from a Windows 11 OS  


