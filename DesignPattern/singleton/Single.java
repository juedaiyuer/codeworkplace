
public class Single
{
    private static Single my_single = null;

    private Single(){}
    
    public synchronized static Single getInstance()
    {
	if(my_single == null)
	    my_single = new Single();
	return my_single;
    } 
    
    public void display()
    {
	System.out.println("singleton test ");
    }
}
