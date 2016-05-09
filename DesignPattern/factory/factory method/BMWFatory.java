public class BMWFactory implements Factory
{
	public Car getCar()
	{
		return new BMW();
	}
}
