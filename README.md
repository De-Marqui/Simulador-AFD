# Simulador-AFD
Simulador de Autômato Finito Determinístico

<pre><code><b><i>Deterministic Finite Automaton Configuration (.txt)</i></b>

2         • 1º line ->  Number of Alphabet Symbols
a b       • 2º line ->  Alphabet Itself
2         • 3º line ->  Number of States in DFA
1         • 4º line ->  Number of Final States
1         • 5º line ->  The Number(s) Corresponding to the Final State(s)
4         • 6º line ->  Number of Machine Transitions and Transitions in the Format <b>[currentState] " " [Symbol] " " [arrivalState]</b>
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
