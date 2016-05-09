public class Singledemo
{
    public static void main(String[] args)
    {
	Single rose = Single.getInstance();
	Single jack = Single.getInstance();
	rose.display();
	jack.display();
    }
}
