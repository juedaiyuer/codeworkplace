public class demo
{
	public static void main(String[] args)
	{
		ChinaCook cc = new ChinaCook();
		Strategy my = new Strategy(cc);
		my.action();
	}
}
