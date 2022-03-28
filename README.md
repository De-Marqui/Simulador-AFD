# CPP DFA Simulator
This DFA Simulator Project was the result of the Mackenzie Presbyterian University project, with a little bit effort I (Victor De Marqui), Gustavo Hiroshi and Guilherme Rodrigues managed to build and bring this simulator to life, of course it has a lot to evolve, but feel free to share your ideas and suggestions with us, hope y'all enjoy it, that's it!
<br><br>
- Explanation of the .txt Files Formation Configuration

<pre><code><b><i>Deterministic Finite Automaton Configuration (.txt)</i></b>

2         • 1º line ->  Number of Alphabet Symbols (qtd ∑)
a b       • 2º line ->  Alphabet Itself (∑)
2         • 3º line ->  Number of States in DFA (Q)
1         • 4º line ->  Number of Final States (qtd F)
1         • 5º line ->  The Number(s) Corresponding to the Final State(s) (F)
4         • 6º line ->  Number of Machine Transitions and Transitions in the Format <b>[currentState] " " [Symbol] " " [arrivalState]</b> (qtd δ n' δ) 
0 a 0     
0 b 1    
1 a 1     
1 b 0  </code> 
</pre>

<pre><code><b><i>Strings File Configuration (.txt)</i></b>

5         • 1º line ->  Number of Strings Lines to be Evaluated
aab       
aababab
abab
bbaa
b</code> 
</pre>
<br>

The DFA analyzed and used for the creation and formulation of the .txt configuration files was: <br>
**M = ( Q, ∑, δ, q0, F )**
> **Q** = _{ q0, q1 }_ <br>
> **∑** = _{ a, b }_ <br>
> **q0** = _q0_ <br>
> **F** = _{ q1 }_ <br>
> <br>
> **δ**: <br>
> **f( q0, a )** = _q0_ <br>
> **f( q0, b )** = _q1_ <br>
> **f( q1, a )** = _q1_ <br>
> **f( q1, b )** = _q0_ <br>
<img src="https://cdn.discordapp.com/attachments/820795354823786508/957798588707135529/Sem_Titulo-1.png">

<br>
<br>

## Program Execution

When starting the program, a menu appears with 5 options to be selected, to select others besides 0 and 1, read the AFD .txt data/configuration:

> 1. Read AFD data from .txt file
> 2. Show the quintuple for the read AFD .txt file
> 3. Evaluate strings read from .txt file
> 4. Evaluate new strings by keyboard input
> 0. close application

`1.` If the .txt file is correctly configured, a success message should be displayed to inform <br><img src="https://cdn.discordapp.com/attachments/820795354823786508/957807235696844830/unknown.png">

`2.` M = ( Q, ∑, δ, q0, F ) <br><img src ="https://cdn.discordapp.com/attachments/820795354823786508/957807307171967027/unknown.png">

`3.` If the .txt file is correctly configured, the Accept/Reject strings should be displayed properly <br> <img src="https://cdn.discordapp.com/attachments/820795354823786508/957808116060278854/unknown.png">

`4.` Just Type any strings you want to check <br><img src="https://cdn.discordapp.com/attachments/820795354823786508/957808266346385418/unknown.png">
