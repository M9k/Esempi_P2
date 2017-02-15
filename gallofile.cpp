#include <vector>
#include <stdexcept>
using std::vector;

class GalloFile
{
private:
	double dim;
public:
	GalloFile(double dimensione) : dim(dimensione) {}
	virtual GalloFile* clone() const = 0;
	virtual bool highQuality() const = 0;
	double getSize() const {return dim;}
};

class Foto : public GalloFile
{
private:
	unsigned int sens;
	bool flash;
public:
	Foto(double dimensione, unsigned int sensibilita, bool conflash) : GalloFile(dimensione), sens(sensibilita), flash(conflash) {}
	virtual Foto* clone() const {return new Foto(*this);}
	virtual bool highQuality() const { return sens >=500;}
	bool withFlash() const {return flash;}
};

class Video : public GalloFile
{
private:
	double sec;
	bool hd;
public:
	Video(double dimensione, double secondi, bool highquality): GalloFile(dimensione), sec(secondi), hd(highquality) {}
	virtual Video* clone() const {return new Video(*this);}
	virtual bool highQuality() const {return hd;}
};

class Gallo
{
private:
	vector<GalloFile*> v;
public:
	vector<GalloFile*> selectHQ() const
	{
		vector<GalloFile*> rit;
		for(vector<GalloFile*>::const_iterator i=v.begin(); i!=v.end(); ++i)
			if((*i)->highQuality())
				if(dynamic_cast<Foto*>(*i))
				{
					if(static_cast<Foto*>(*i)->withFlash())
						rit.push_back(*i);
				}
				else
					rit.push_back(*i);
		return rit;
	}
	
	void removeNonFoto(double size)
	{
		bool eliminati = false;
		for(auto i=v.begin(); i!=v.end(); ++i)
			if(!dynamic_cast<Foto*>(*i) && (*i)->getSize() > size)
			{
				delete *i;
				i = v.erase(i);
				i--;
				eliminati = true;
			}
		if(!eliminati)
			throw std::logic_error("NoRemove");
	}
	
	const GalloFile* insert(const GalloFile* pf)
	{
		v.push_back(pf->clone());
		return *(--v.end());
	}
};