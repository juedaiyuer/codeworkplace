public class Strategy
{
	private Cookfish cookfish;
	public Strategy(Cookfish cookfish)
	{
		this.cookfish = cookfish;
	}

	public void action()
	{
		this.cookfish.cookfish();
	}
}
