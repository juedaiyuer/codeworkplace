public class Factory
{
    public Car getCar(String name)
    {
	if(name.equals("Benz"))
	    return new Benz();
	else if(name.equals("BMW"))
	    return new BMW();
	else
	    return null;				
    }	
}
