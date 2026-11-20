# **OS Lab 2 — Linux commands revision**

## **1. Ubuntu directory structure**

First, understand these directories. They are common theory questions.

| Directory | Purpose                                      |
| --------- | -------------------------------------------- |
| `/`       | Root directory; starting point of filesystem |
| `/bin`    | Common user commands                         |
| `/sbin`   | System administration commands               |
| `/etc`    | Configuration files                          |
| `/dev`    | Device files                                 |
| `/proc`   | Process and system information               |
| `/var`    | Variable data, logs                          |
| `/tmp`    | Temporary files                              |
| `/usr`    | User programs and libraries                  |
| `/home`   | Users' personal directories                  |
| `/boot`   | Bootloader and kernel files                  |
| `/lib`    | System libraries                             |
| `/opt`    | Optional applications                        |
| `/mnt`    | Temporary mount point                        |
| `/media`  | Removable devices                            |
| `/srv`    | Service-related data                         |

**Important exam difference:**

- `/` = root of the entire filesystem.
- `/root` = home directory of the root user.
- `/home` = home directories of normal users.

## **2. Basic commands**

### **A.&#x20;**`man`**&#x20;— Manual**

Displays the manual/help page for a command.

```
man ls
man grep
man mkdir
```

Press `q` to exit the manual.

### **B.&#x20;**`ls`**&#x20;— List files**

| Command | Purpose                                          |
| ------- | ------------------------------------------------ |
| `ls`    | List files and directories                       |
| `ls -a` | Show hidden files                                |
| `ls -l` | Detailed listing                                 |
| `ls -R` | List files recursively, including subdirectories |

Example:

```
ls
ls -a
ls -l
ls -R
```

Remember: hidden files normally begin with a dot (`.`), such as `.bashrc`.

### **C. Creating and viewing files**

| Command          | Purpose                         |
| ---------------- | ------------------------------- |
| `gedit file.txt` | Open/create file in text editor |
| `cat > file.txt` | Create file and enter text      |
| `touch file.txt` | Create an empty file            |
| `cat file.txt`   | Display file content            |

Example:

```
touch os.txt
cat > os.txt
```

Enter your text, then press `Ctrl + D` to finish.

To display:

```
cat os.txt
```

### **D. Combining files**

```
cat file1.txt file2.txt > combined.txt
```

Combines the contents of two files into a new file.

### **E. Page-wise content**

```
less os.txt
```

Useful for reading large files page by page.

Inside `less`:

- `/word` = search for a word.
- `n` = next occurrence.
- `q` = quit.

## **3. File manipulation commands**

| Command | Purpose     | Example                |
| ------- | ----------- | ---------------------- |
| `rm`    | Delete file | `rm os.txt`            |
| `mv`    | Move file   | `mv os.txt ~/Desktop/` |
| `mv`    | Rename file | `mv old.txt new.txt`   |
| `cp`    | Copy file   | `cp os.txt copy.txt`   |

**Very important difference:**

- `mv` moves or renames.
- `cp` copies.
- `rm` deletes.

## **4. Searching commands**

### **A.&#x20;**`grep`

Searches for specific words or patterns inside files.

```
grep science os.txt
```

Important options:

| Command                         | Purpose                         |
| ------------------------------- | ------------------------------- |
| `grep science os.txt`           | Search exact case               |
| `grep -i science os.txt`        | Ignore uppercase/lowercase      |
| `grep -v science os.txt`        | Display lines that do not match |
| `grep -n science os.txt`        | Show matching line numbers      |
| `grep -c science os.txt`        | Count matching lines            |
| `grep -i 'spinning top' os.txt` | Search a phrase                 |

**Exam point:** `grep` is case-sensitive by default.

### **B.&#x20;**`wc`**&#x20;— Word count**

```
wc -w os.txt
wc -l os.txt
```

- `-w` = count words.
- `-l` = count lines.

### **C. Appending to a file**

```
cat >> list1
```

Adds new content at the end of an existing file.

Press `Ctrl + D` when finished.

**Difference:**

- `>` overwrites the file's existing content.
- `>>` appends content without removing existing content.

## **5. Directory manipulation commands**

### **A.&#x20;**`mkdir`**&#x20;— Create directory**

```
mkdir OS
```

Creates a directory named `OS`.

### **B.&#x20;**`cd`**&#x20;— Change directory**

| Command | Purpose                   |
| ------- | ------------------------- |
| `cd OS` | Enter OS directory        |
| `cd ..` | Go one directory up       |
| `cd .`  | Stay in current directory |
| `cd`    | Return to home directory  |
| `cd ~`  | Go to home directory      |

### **C.&#x20;**`pwd`**&#x20;— Present working directory**

```
pwd
```

Displays the full path of your current directory.

### **D.&#x20;**`rmdir`**&#x20;— Remove directory**

```
rmdir OS
```

Removes an empty directory.

**Important:** `rmdir` cannot remove a directory containing files or subdirectories.

### **E. Renaming directories**

Use `mv`:

```
mv OS OS-Lab
```

### **F. Copying directories**

Use `cp -r`:

```
cp -r OS OS-Copy
```

`-r` means recursive: copy the directory and its contents.

## **6. Permissions —&#x20;**`ls -l`**&#x20;and&#x20;**`chmod`

This is an important practical and theory topic.

Run:

```
ls -l
```

Example output:

```
-rwxrw-r-- 1 user group 2450 file1
```

Understand these symbols:

| Symbol | Meaning                  |
| ------ | ------------------------ |
| `r`    | Read                     |
| `w`    | Write                    |
| `x`    | Execute                  |
| `-`    | Permission not available |
| `d`    | Directory                |

Permissions are divided into three groups:

1. User/Owner
2. Group
3. Others

For example:

```
-rwx rw- r--
```

- Owner: read, write, execute.
- Group: read, write.
- Others: read only.

### `chmod`**&#x20;— Change permissions**

| Symbol | Meaning           |
| ------ | ----------------- |
| `u`    | User/Owner        |
| `g`    | Group             |
| `o`    | Others            |
| `a`    | All               |
| `+`    | Add permission    |
| `-`    | Remove permission |

Examples from your lab:

```
chmod go-rwx os.txt
```

Removes read, write, and execute permissions from group and others.

```
chmod a+rw os.txt
```

Adds read and write permissions for everyone.

Check the result:

```
ls -l
```

## **7. Other useful Linux commands**

### **A.&#x20;**`clear`

```
clear
```

Clears the terminal screen.

### **B. Redirection**

Redirection changes where command input or output goes.

| Operator | Purpose                         |
| -------- | ------------------------------- |
| `>`      | Redirect output; overwrite file |
| `>>`     | Redirect output; append to file |
| `<`      | Take input from a file          |

Examples:

```
who > names.txt
```

Saves the output of `who` into `names.txt`.

```
sort < names.txt
```

Takes input from `names.txt` and sorts it.

```
sort < names.txt > sorted.txt
```

Sorts the file and saves the result in `sorted.txt`.

### **C. Pipes&#x20;**`|`

A pipe sends the output of one command directly as input to another command.

```
who | sort
```

Displays sorted user information.

```
who | wc -l
```

Counts the number of logged-in users.

**Exam difference:**

- `>` redirects output to a file.
- `|` sends output to another command.

### **D. Wildcards**

Wildcards are used to match filenames.

| Wildcard | Meaning                         |
| -------- | ------------------------------- |
| `*`      | Matches zero or more characters |
| `?`      | Matches exactly one character   |

Examples:

```
ls list*
ls *list
ls ?ouse
```

- `list*` matches filenames beginning with `list`.
- `*list` matches filenames ending with `list`.
- `?ouse` matches names such as `house` and `mouse`.

### **E.&#x20;**`history`

```
history
```

Displays previously used commands.

### **F.&#x20;**`sudo`

Runs a command with administrator privileges.

```
sudo command
```

Example:

```
sudo apt update
```

It may ask for your account password.

## **8. Complete command cheat sheet**

Save this table for quick revision.

| Command   | Main purpose                        |
| --------- | ----------------------------------- |
| `man`     | Open command manual                 |
| `ls`      | List files                          |
| `ls -a`   | Show hidden files                   |
| `ls -l`   | Detailed listing                    |
| `ls -R`   | Recursive listing                   |
| `gedit`   | Open text editor                    |
| `cat`     | Create/display/combine file content |
| `touch`   | Create empty file                   |
| `less`    | View file page-wise                 |
| `rm`      | Delete file                         |
| `mv`      | Move or rename                      |
| `cp`      | Copy file                           |
| `grep`    | Search text                         |
| `wc`      | Count words/lines                   |
| `mkdir`   | Create directory                    |
| `cd`      | Change directory                    |
| `pwd`     | Show current path                   |
| `rmdir`   | Remove empty directory              |
| `chmod`   | Change permissions                  |
| `clear`   | Clear terminal                      |
| `sort`    | Sort input                          |
| `who`     | Show logged-in users                |
| `history` | Show command history                |
| `sudo`    | Run with administrator privileges   |

