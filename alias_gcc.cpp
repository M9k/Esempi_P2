/*
	`7MMM.     ,MMF'        `7MM      
	  MMMb    dPMM            MM      
	  M YM   ,M MM  .d*"*bg.  MM  ,MP'
	  M  Mb  M' MM 6MP    Mb  MM ;Y   
	  M  YM.P'  MM YMb    MM  MM;Mm   
	  M  `YM'   MM  `MbmmdM9  MM `Mb. 
	.JML. `'  .JMML.     .M'.JMML. YA.
					   .d9            
					 m"'        Mirco Cailotto
-
-				 
	Compilatore: 
	gcc (tdm64-1) 4.9.2, nessun parametro aggiuntivo
*/

#include <iostream>

using std::cout;
using std::flush;

void f1(int& a)
{
	a++;
}
void f2(const int& a)
{
	int b = a*3;
}

int main()
{
	cout << "inizio\n";
	int a = 123;
	f1(a);
	f2(345);
	cout << "fine\n";
}
/*
	Decompilatore: x64dbg (lavoro sotto Windows)
	Il main, senza stampe, si presenta così:
mov dword ptr ss:[rbp-8],7B								"dichiara" la variabile nello stack
lea rax,qword ptr ss:[rbp-8]							mette in rax l'indirizzo effettivo della variabile (lea = load effective address)
mov rcx,rax												sposta il contenuto di rax in rcx
call alias_gcc.401530									chiama la prima funzione -> andrà a prelevare e modificare il contenuto di rcx
mov dword ptr ss:[rbp-4],159
lea rax,qword ptr ss:[rbp-4]
mov rcx,rax
call alias_gcc.401549									la seconda funzione

alla terza istruzione sposta in rcx il valore rax=6FFE48
Nel dump il valore indicato da 6FFE48 (che appartiene allo stack) è 7B, in binario 123
successivamente nella funzione alias_gcc.401530 viene pescato l'indirizzo, modificato e risalvato, che è esattamente il comportamento di un puntatore.

Per quanto riguarda il 345, cioè 159 in hex, si nota l'istruzione
mov dword ptr ss:[rbp-4],159
Praticamente identico alla "dichiarazione di a", che era
mov dword ptr ss:[rbp-8],7B
si nota la stessa identica istruzione, ovviamente su un'altra porzione dello stack.
Alla fine la sezione di stack usata è così composta:
00000000006FFE48  000001590000007C

Il secondo mov rcx,rax, in esecuzione, presenta questi valori:
rcx=6FFE48
rax=6FFE4C
Se la sostituisco con 3 nop (perchè l'istruzione originaria è di 3 byte, mentre nop ne occupa solo uno, quindi devo pur riempire lo spazio in più)
la seconda funzione, invece di moltiplicare 345, moltiplicherà 123, perchè rcx non sarà modificato e punterà ancora a.

NOTA:
La moltiplicazione è così eseguita:
mov edx,dword ptr ds:[rax]
mov eax,edx
add eax,eax
add eax,edx
Invece di moltiplicare il valore per 3 preferisce caricarlo in edx, copiarlo in eax, sommare a eax se stesso e poi edx.

*/