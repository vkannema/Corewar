<img src="https://cdn.rawgit.com/emilwallner/Corewar/master/images/corewarlogo.svg" width="100%">

---

**Core War was inspired by a malicious virus written in the 80’s.** To deal with the self-replicating virus, a white hat hacker invented Reaper. It was a virus designed to spread and eliminate the malware. He fought fire with fire.

This inspired A. K. Dewdney to coin the idea for Core War.

The idea was simple. You compete by designing viruses to overtake a computer. You win by protecting your own program and overwriting your opponent's programs. This is all happening on a virtual computer. Think, a simple computer within your computer. 

This is what is looks like in action:

![Alt text](http://g.recordit.co/pyyAggYcWm.gif "Optional title")

Let’s focus on the high-level game dynamics: 

- **The game board**, the memory of our virtual computer. It’s represented in a 64 X 64 grid of bytes.
- **The players**, small programs represented in different colors. The white parts have blank memory.
- **Cursors**, the moving parts with inverted color. They read from the game board. 

The cursors have a couple of features. They can jump on the game board, store and write values, and clone themselves. The cursors belong to no-one, they just read from the game board.

When the game starts, all players have one cursor at the beginning of their program. The game advances as the cursors read the commands stored in their programs. If they end up on a faulty command or a blank memory, it moves to the next byte. 

Below, we see how the pink player starts by cloning their cursors. It then starts attacking the blue player.

![Alt text](http://g.recordit.co/Y9r9E78FVY.gif "Optional title")

Let’s get into a little bit more depth. 

Every byte you see, the pairs of numbers or letters, are represented in hexadecimal. Each hexadecimal has the value of a digit, from 0 - 255. 

There are 16 operations in the game. The operations decide if the cursor should jump to a different address, clone itself and so on. The first 16 hexadecimal are [**coding bytes**](https://docs.google.com/spreadsheets/d/1IuQv2yfx7ewS3d6H2KyDu7N9U67u3mhFBy8W1XUhxuM/edit?usp=sharing), they all store a different operation. The remaining digits, 17 - 255, are regular numbers. 

The coding byte decides which operation to execute and how many bytes to read. In the image above, the pink player goes to the hexadecimal **0c**. It's 12 in decimal, telling the cursor to clone itself. The two bytes after decide where the cloned cursor starts. 

![Alt text](http://g.recordit.co/XQdhVmqvrV.gif "Optional title")

There are three main components to determine who wins: 

- **Game rounds**, every game round is measured in cycles. It determines how much each cursor can read from the game board. 
- **Lives**, if a cursor reads a player life from the game board, they are given a life for that round. These are visualized in the colorful progress bars. 
- **Cycle to die**, for every game round, the number of bytes a cursor can read from the game board is reduced.

You win if your program is the last one to receive a life. 

There are more nuances to the game that I don’t cover. The best way to learn about them is to run it with the below code.  

<br>
<br>

## Executing Core War

Open your terminal and make it full-screen, copy paste the below, and hit enter.

```shell
git clone https://github.com/vkannema/Corewar 
cd Corewar
make
./Corewar -i ./Players/bigzork.cor ./Players/fluttershy.cor ./Players/turtle.cor ./Players/helltrain.cor
```

Once the cycle to die reaches 0, it will announce a winner. Then you can press any key to leave the program.

The usage for the Core War game: 

```
Usage:
 	Example: ./corewar -i -n -1 filename.cor
 	GUI: ./corewar -i [Players]
 	Default Player Numbers: 1, 2, 3, 4...
 	Change Player Number: -n -1 filename.cor
 	Dump: ./corewar -dump 300 [Players](prints the memory after 300 cycles)
 	Game on! 👾 🤖 🔫
```
If you want to create and then compile players, use the asm: 

```
./asm [filename.s]
```

### Control the visualiser

Once you launched the visualiser with the -i option; you will have a black screen. Then you can select
	- press 1 to stop at every cycle of the game
	- press 2 to stop every 5 cycles
	- press 3 to stop every 10 cycles
	- press 4 to stop every 100 cycles
	- press space to start the game without the possibility to stop it.

<br>
<br>

This is an example of a simple player, a normal player has around 150 lines of assembly code:

```assembly
    .name "zork"
    .comment "I'M ALIIIIVE"
    
    l2:          sti r1,%:live,%1
                 and r1,%0,r1
    
    live:        live %1
                 zjmp %:live
```


That’s it for me. If you have any questions or find and issues with the game, ping me an email. 
