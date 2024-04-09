
# Circuitikz Code

The idea is take a qucs .sch file and convert it to a LaTeX Circuitikz package code.
A ideia é pegar um código .sch do qucs e converter para um código do pacote Circuitikz do LaTeX.

links importantes:

Explicação dos parâmetros dos arquivos *.sch do Qucs: https://qucs-help.readthedocs.io/en/0.0.18/internal.html


### Compilação - Compilation

It uses simple C and C++ libs. To compile it just tipe:

	g++ main.cpp -o circuit-code

on your terminal and it will create the executable.

* If you want to execute anywhere, copy the executable to $HOME/.local/bin directory
* Use like:

    circuit-code qucs_schematic.sch

It can read any file, actualy. But it only translates to Latex-Circuitikz if it sees the qucs file format data inside the file readed.
