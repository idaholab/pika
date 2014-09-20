# Pika: Phase-field Snow Micro-structure Model

[gimmick:ForkMeOnGitHub (position: 'right', color: 'darkblue') ](http://www.github.com/idaholab/pika)

## Overview
Pika is a phase-field micro-structure model for dry snow that was developed using the [MOOSE](https://www.mooseframework.org) framework at the [Idaho National Laboratory](https://www.inl.gov) following the work of [Kaempfer and Plapp (2009)](http://journals.aps.org/pre/abstract/10.1103/PhysRevE.79.031502). It is a fully-coupled 3D finite element, phase field model capable of tracking the phase transition and capturing the heat and mass transfer at the micro-structure scale in the ice matrix and pore space.

## Getting Started
1. Install MOOSE: http://mooseframework.org/getting-started/
2. Download Pika by forking or cloning:
    * **Fork**: If you plan on contributing changes you should work in your own fork of Pika and submit changes via "Pull Requests." This is done by first creating your fork via the GitHub interface and then cloning your fork with the following command from the same directory as MOOSE was installed (typically ```~/projects```).
    ```
    git clone git@github.com:<your GitHub username here>/pika.git
    ```
    Pika follows the same methodolgy for development as the [MOOSE](https://www.mooseframework.org) framework itself, thus for more information about contributing code to Pika refer to http://mooseframework.org/wiki/Contributing.
    * **Clone**: If you only plan to use or just want to try-out Pika then simply cloning Pika is generally the best coarse of action. Run the following command from the directory that contains the MOOSE root directory (typically a directory named ```projects``` in your home directory).
    ```
    git clone git@github.com:idaholab/pika.git
    ```
3. Build Pika:

   ```
   cd ~/projects/pika
   git checkout master
   make -j8
   ```
4. Test Pika:

    ```
    ./run_tests -j8
    ```

## Contacts
This projects is under the direction of Andrew E. Slaughter please contact him at andrew.slaughter@inl.gov for more information.
