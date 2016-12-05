#include <iostream>
#include <vector>
#include <string>

using std::cout;
using std::vector;
using std::string;

class FileAudio
{
	private:
	string titolo;
	double dimensione; //in MB
	public:
	virtual FileAudio* clone() const = 0;
	virtual bool qualita() const = 0; //vero o falso se è di qualità
	virtual ~FileAudio() {} //per evitare leak di memoria
	FileAudio(string t, double d) : titolo(t), dimensione(d) {}
	double getDimensione() const {return dimensione;}
};

class Mp3: public FileAudio
{
	private:
	int bitrate;
	static int bitratequalita;
	public:
	virtual FileAudio* clone() const;
	virtual bool qualita() const;
	Mp3(string t, int b, double d=0): FileAudio(t, d), bitrate(b) {}
	int getBitrate() const {return bitrate;}
};

class wav: public FileAudio
{
	private:
	int campionamento;
	static int campionamentoqualita;
	bool lossless;
	public:
	virtual FileAudio* clone() const;
	virtual bool qualita() const;
	wav(string t, int c, double d, bool ll=false): FileAudio(t, d), campionamento(c), lossless(ll) {}
	bool is_lossless() const {return lossless;}
};

// -- Mp3 --
int Mp3::bitratequalita = 192;
FileAudio* Mp3::clone() const
{
	return new Mp3(*this); //costruttore di copia
}
bool Mp3::qualita() const
{
	return bitrate>=bitratequalita;
}
// -- wav --
int wav::campionamentoqualita = 96;
FileAudio* wav::clone() const
{
	return new wav(*this); //costruttore di copia
}
bool wav::qualita() const
{
	return campionamento>=campionamentoqualita;
}

//------------------------------------------------------------------

class iZod
{
	private:
	class Brano
	{
		public:
		FileAudio* traccia;	//anche pubblica perchè comunque non accessibile dall'estrno di iZod
		//devo costruire una copia del riferimento passato
		Brano(FileAudio* tr): traccia(tr->clone()) {}
		FileAudio* getTraccia() const {return traccia;}
		//regola del 3
		Brano(const Brano& b) : traccia(b.traccia->clone()) {}
		~Brano();
		Brano& operator =(const Brano&);
	};
	vector<Brano> lista;
	public:
	vector<Mp3> mp3(double, int) const;	//richiesto come vector di oggetti
	vector<FileAudio*> braniQual() const;
	void insert(Mp3*);
	void insert_anyway(FileAudio* f) {lista.push_back(Brano(f));} //no new Brano, è il brano che gestisce la memoria
};

// -- brano --
iZod::Brano::~Brano()
{
	delete traccia;
}
iZod::Brano& iZod::Brano::operator =(const Brano& b)
{
	if(this != &b)
	{
		//if(traccia)
		delete traccia;
		traccia = b.traccia->clone();
	}
	return *this;
}
// -- iZod --
vector<Mp3> iZod::mp3(double dim, int br) const
{
	vector<Mp3> ret;
	for(vector<Brano>::const_iterator i = lista.begin();i != lista.end();i++)
	{
		if(const Mp3* m = dynamic_cast<Mp3*>((*i).getTraccia())) //controllo che sia Mp3 O un suo derivato
			if((*m).getDimensione() > dim || (*m).getBitrate() > br)
				ret.push_back(*m);
	}
	return ret;
}

vector<FileAudio*> iZod::braniQual() const
{
	vector<FileAudio*> ret;
	for(vector<Brano>::const_iterator i = lista.begin();i != lista.end();i++)
	{
		if((*i).getTraccia()->qualita())
		{
			if(const wav* w = dynamic_cast<wav*>((*i).getTraccia())) //controllo se è un WAV o derivato
			{
				if(w->is_lossless())
					ret.push_back((*i).getTraccia());
			}
			else
				ret.push_back((*i).getTraccia());
		}
	}
	return ret;
}

void iZod::insert(Mp3* add)
{
	bool trovato = false;
	for(vector<Brano>::const_iterator i = lista.begin();i != lista.end() && !trovato;i++)
	{
		if(add == dynamic_cast<Mp3*>(i->getTraccia())) //se cast non valido restituisce 0, 0 diverso da add
			trovato = true;
	}
	if(!trovato)
		lista.push_back(add);	//upcast Mp3* -> FileAudio*
}

int main()
{
	iZod i1;
	//FileAudio fa("canzone1");
	Mp3 m1("1", 200, 52), m2("2", 150, 6), m3("3",100, 1), m4("4",10,45);
	Mp3 *m5 = new Mp3("3", 123, 54);
	Mp3 m6(m2);
	wav w1("sasd", 100, 2), w2("asd", 10, 23, true);
	FileAudio* a1 = new wav("sasd", 100, 78, false);
	
	i1.insert_anyway(&m1);
	i1.insert_anyway(&m2);
	i1.insert_anyway(&m3);
	i1.insert(&m4);
	i1.insert(m5);
	i1.insert_anyway(&w1);
	i1.insert_anyway(&w2);
	i1.insert_anyway(a1);
	i1.braniQual();
	i1.mp3(12, 120);
	
	delete m5;
	delete a1;
	cout << "fine\n";
	return 0;
}