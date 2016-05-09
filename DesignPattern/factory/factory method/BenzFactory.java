public class BenzFactory implements Factory
{
	public Car getCar()
	{
		return new Benz();
	}
}
