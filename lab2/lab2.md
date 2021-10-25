# VE482 Lab 2 <span style="font-family:Myriad Pro; font-size:0.6em;">                     Weili Shi 519370910011                             Oct 1, 2021</span>

## 1. Minix 3

- Software management

  ```shell
  # to install
  pkgin install $PACKAGENAME
  # to remove
  pkgin remove $PACKAGENAME
  # to update
  pkgin update
  ```

- `ifconfig`: configure a network interface, display information about the network.
- `adduser`: add a user or group to the system
- `passwd`: change the passwords for user accounts

## 2. Working on a remote server

- Setup an SSH server on Minix3.

  ```sh
  pkgin update
  pkgin install openssh
  vi /usr/pkg/etc/ssh/sshd_config
  # The default SSH port is 22.
  # On line 13, delete # and change the line to Port 2222.
  ssh root@192.168.130.138 -p 2222
  # log into minix3 with ssh
  ```

- Files in `$HOME/.ssh`
  - `known_hosts`: a list with an identifier for each server to which we connect.
  - `id_ed25519`: private key. The file can also be `id_rsa` because of different encryption.
  - `id_ed25519.pub`: public key. The file can also be `id_rsa`.
  - `config`: the configuration file for ssh.
  
- Key-only authentication in SSH

  The user generates a pair of keys, one public and one private. The public key is sent to the server and the server adds the key to the list of authorized hosts. To log in, the user sends the public key to the server. If the keys are matched, a connection is made.

## 3. Basic git

- `help`: displays common commands of git.
- `init`: initialize an empty local git repository.
- `checkout`: checkout to another branch.
- `branch`: list, create or delete branches.
- `push`: update remote references along with associated objects.
- `pull`: fetch from and integrate another repository or a local branch.
- `merge`: join multiple branches together.
- `add`: add file contents to the index.
- `diff`: show changes between commits or commit and the working tree.
- `tag`: create, list, delete or verify a tag object signed with GPG.
- `log`: show the commit logs.
- `fetch`: download objects and refs from another repository.
- `commit`: record changes to the repository.
- `clone`: clone a repository into a new directory.
- `reset`: reset current HEAD to the specified state.

