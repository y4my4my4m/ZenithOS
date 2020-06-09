CAHCIPort *x = MAlloc(30);
x->cmd_list_base = 0xAAAAAAAA;
x->cmd_list_base_upper = 0xFFFF;

U0 Method1()
{
	I64 i = *&x->cmd_list_base(I64 *);
}

U0 Method2()
{
	I64 i = x->cmd_list_base_upper << 32 | x->cmd_list_base;
}

Method1;
Method2;

Uf("Method1");
Uf("Method2");
