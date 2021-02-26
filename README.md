# Table of Contents
 - [Corewar](#corewar)
- [Table of Contents](#table-of-contents)
- [Corewar](#corewar)
- [Motivation](#motivation)
- [Screenshots](#screenshots)
- [Installation & How to use?](#installation--how-to-use)
  - [Virtual Machine](#virtual-machine)
  - [Assembler](#assembler)
  - [Visualiser](#visualiser)
- [Contribute](#contribute)
- [Resources](#resources)
- [Contributers](#contributers)


# Corewar

Corewar is one of the interesting projects in our 1337 curriculum, where we had the opportunity to write an emulation `VM` of the computer components. The RAM, Process, Threads, scheduling, and other interesting subjects were just one side of this team project. the other ones were a visualizer of the state of our VM and an `ASUMBLER` program that compiles assembly files to binary ones, and these last ones we can run in our VM and visualize them.


# Motivation
  In this Project we were a team of 4 students, that got a totally new topic with very little guidance, but a lot of motivation to explore this new topic.

  And that what happed, during the preparation, the coding, and the debugging we've learned how computers work at the low level, the magic of processes, threads, and CPU segments.

  these are all now just a part of our DNA now 😉  

# Screenshots

# Installation & How to use?
1. open your terminal of choice and run these commands in order.
2. `git clone https://github.com/mohamedLazyBob/corewar.git`
3. `make all`


## Virtual Machine

The `VM` programe accepts 1 to 4 programs, and can be runed with different options. I'll leave it to you to discover them.
```bash
Usage: ./corewar [ -d N  -s N  -v N ] [-a] <champion1.cor> <...>
        -a / --aff       : Prints output from "aff" (Default is to hide it)
#### TEXT OUTPUT MODE ########################################################## 
        -d / --dump   N    : Dumps memory after N cycles then exits
        -s / --pause  N    : Runs N cycles, dumps memory, pauses, then repeats
        -v / --verbos N    : Verbosity levels, can be added together to enable several
                                - 0 : Show only essentials (introduction + the winner)
                                - 1 : Show lives
                                - 2 : Show cycles
                                - 4 : Show operations (Params are NOT litteral ...)
                                - 8 : Show deaths
                                - 16 : Show PC movements (Except for jumps)
#### visualization OUTPUT MODE ################################################ 
        -n / --visu    : visualization output mode
################################################################################ 
```
## Assembler
- `./asm <One assbembly file>`

  --> this converts the assembly file to a binary file.

## Visualiser
- **[] TODO: I think this could use some more explanaition!**

# Contribute
If you would like to add new things and contribute to our project you're welcome, just fork it, code your ideas and create a pull request!

# Resources
- [official subject guide](./resources/off_corewar.en.pdf)  
- [official advices resources](./resources/off_resources_corewar.en.pdf)  

- [the Original Corewar game](https://en.wikipedia.org/wiki/Core_War)  
- [Russion cookBook](https://github.com/VBrazhnik/Corewar/wiki)   
- [English cookBook](https://github.com/k-off/Corewar/wiki)  

- [Corewar Cheat sheet](./resources/Corewar_Cheat_Sheet.pdf)
- [the operations explained by jyeo](./resources/corewar_operations_by_jyeo.pdf)

**TODO: everyone should add some of his resources to this**

# Contributers

Collaboration between

| <img src="https://avatars.githubusercontent.com/u/45185441?s=100" width="50px" style="border-radius: 50%;" /> | <img src="https://avatars.githubusercontent.com/u/40963149?s=100" width="50px" style="border-radius: 50%;" /> | <img src="https://avatars.githubusercontent.com/u/47392041?s=100" width="50px" style="border-radius: 50%;" /> | <img src="https://avatars.githubusercontent.com/u/24608280?s=100" width="50px" style="border-radius: 50%;" /> |
| ------------------------------------------------------------------------------------------------------------- | ------------------------------------------------------------------------------------------------------------- | ------------------------------------------------------------------------------------------------------------- | ------------------------------------------------------------------------------------------------------------- |
| [LazyBob](https://github.com/mohamedLazyBob)                                                                  | [Douae](https://github.com/del-alj)                                                                           | [Mohamed](https://github.com/MohammedEsafi)                                                                   | [tareq](https://github.com/tareqbareich)                                                                      |