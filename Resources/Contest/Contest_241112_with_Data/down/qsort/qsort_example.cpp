struct number
{
	bool isnan;
	int value;
};
bool operator < (const number& x, const number& y)
{
	if(x.isnan || y.isnan)
		return false;
	return x.value < y.value;
}
number tmp[1 << 20];
void qsort(number* _begin, number* _end)
{
	if(_begin + 1 >= _end)
		return;
	number a = *_begin, *s = _begin, *t = tmp;
	for(number* p = _begin + 1; p < _end; p++)
	{
		if(*p < a)*s = *p, s++;
		else *t = *p, t++;
	}
	*s = a, s++;
	for(t--; t >= tmp; t--) *(s + (t - tmp)) = *t;
	qsort(_begin, s - 1);
	qsort(s, _end);
}