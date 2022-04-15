void fillPolygon(const std::vector<V2d> &vertex, int color)
{
	int len = vertex.size();
	struct ET
	{
		double x, dx, ymax; ET *next;
		ET() { x=dx=ymax=0; next=nullptr; }
	};
	// boundary
	int upperBound = vertex[0].y, lowerBound = vertex[0].y;
	for (int i=1; i<len; i++)
	{
		upperBound = _max(upperBound, vertex[i].y);
		lowerBound = _min(lowerBound, vertex[i].y);	
	}
	// NET
	ET *net[2048];
	for (int i=0; i<=upperBound; i++) net[i] = new ET();
	for (int i=lowerBound; i<=upperBound; i++)
	{
		for (int j=0; j<len; j++)
		{
			const V2d &now = vertex[j];
			if (now.y == i)
			{
				const V2d &pre = vertex[(j-1+len)%len];
				const V2d &nxt = vertex[(j+1+len)%len];
				if (pre.y > now.y)
				{
					ET *p = new ET;
					p->x = now.x;
					p->dx = (double)(pre.x-now.x)/(pre.y-now.y);
					p->ymax = pre.y;
					p->next = net[i]->next;
					net[i]->next = p;
				}
				if (nxt.y > now.y)
				{
					ET *p = new ET;
					p->x = now.x;
					p->dx = (double)(nxt.x-now.x)/(nxt.y-now.y);
					p->ymax = nxt.y;
					p->next = net[i]->next;
					net[i]->next = p;
				}
			}
		}
	}

	// AET
	ET *aet = new ET;
	aet->next = nullptr;
	for (int i=lowerBound; i<=upperBound; i++)
	{
		// update x
		ET *p = aet->next;
		while (p)
		{
			p->x = p->x + p->dx;
			p = p->next;
		}
		// sort aet
		ET *t = aet;
		p = aet->next;
		t->next = nullptr;
		while (p)
		{
			while (t->next && p->x >= t->next->x)
				t = t->next;
			ET *s = p->next;
			p->next = t->next;
			t->next = p;
			p = s;
			t = aet;
		}
		// del ymax==i in aet
		t = aet;
		p = aet->next;
		while (p)
		{
			if (p->ymax == i)
			{
				t->next = p->next;
				delete p;
				p = t->next;
			}
			else p = (t=t->next)->next;
		}
		// add new point from net to aet and sort
		p = net[i]->next;
		t = aet;
		while (p)
		{
			while (t->next && p->x >= t->next->x)
				t = t->next;
			ET *s = p->next;
			p->next = t->next;
			t->next = p;
			p = s;
			t = aet;
		}
		// fill
		p = aet->next;
		while (p && p->next)
		{
			int l = p->x+0.5, r = p->next->x+0.5;
			for (int j=l; j<=r; j++)
				putpixel(j, i, color);
			p = p->next->next;
		}
	}
}