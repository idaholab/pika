# Getting Started with Pika

## 1. Install MOOSE
Pika is a [MOOSE](https://www.mooseframework.org)-base application, see http://mooseframework.org/getting-started for detalied instructions.

## 2. Download Pika
There are two main method for retrieving the source code for Pika: Forks and Clones

### Fork Pika
If you plan on contributing changes you should work in your own fork of Pika and submit changes via "Pull Requests." This is done by first creating your fork via the GitHub interface and then cloning your fork with the following command from the same directory as MOOSE was installed (typically ```~/projects```).
``` 
git clone git@github.com:<your GitHub username here>/pika.git
```

Note! Pika follows the same methodolgy for development as the [MOOSE](https://www.mooseframework.org) framework itself, thus for more information about contributing code to Pika refer to http://mooseframework.org/wiki/Contributing.

### Clone Pika  
If you only plan to use or just want to try-out Pika then simply cloning Pika is generally the best coarse of action. Run the following command from the directory that contains the MOOSE root directory (typically a directory named ```projects``` in your home directory).
```bash    
git clone git@github.com:idaholab/pika.git
```

## 3. Compile Pika
The following commands should be executed to compile Pika. Note, the ```git checkout``` command is required to switch from the development branch (devel), which is the default to the fully-tested master branch. Again, if you plan on making changes to Pika refer to http://mooseframework.org/wiki/Contributing.
```bash
cd ~/projects/pika
git checkout master
make -j8
```
   
## 4. Test Pika
```bash
./run_tests -j8
```
