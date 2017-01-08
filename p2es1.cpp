vector<QAbstractButton*> fun(list<QWidget*>& l, const QSize& q)
{
	vector<QAbstractButton*> rit;
	
	for(list<QWidget*>::const_iterator i=l.being(); i!=l.end(); )
	{
		if(dynamic_cast<QCheckBox*>(*i) || dynamic_cast<QPushButton*>(*i))
		{
			rit.push_back(static_cast<QAbstractButton*>(*i));
			i = l.erase(i):
		}
		else
		{
			if((*i) && (*i).sizeHint() == q)
				l.push_front((*i)->clone());
			if((*i) && !dynamic_cast<SAbstractSlider*>(*i) && (*i)->sizeHint() == q)
			{
				delete (*i);
				i = l.erase(i):
			}
			else
				i++;
		}
	}
	return rit;
}

vector<QAbstractButton*> fun(list<QWidget*>& l, const QSize& q)
{
	vector<QAbstractButton*> rit;
	list<QWidget*>::const_iterator ultimo = --rit.end();
	bool fine = false;
	
	for(list<QWidget*>::const_iterator i=l.being(); !fine; )
	{
		if(dynamic_cast<QCheckBox*>(*i) || dynamic_cast<QPushButton*>(*i))
		{
			rit.push_back(static_cast<QAbstractButton*>(*i));
			i = l.erase(i):
		}
		else
		{
			if((*i) && (*i).sizeHint() == q)
				l.push_back((*i)->clone());
			
			if((*i) && !dynamic_cast<SAbstractSlider*>(*i) && (*i)->sizeHint() == q)
			{
				delete (*i);
				i = l.erase(i):
			}
			else
				i++;
		}
		if(i == ultimo)
			fine = true;
	}
	return rit;
}