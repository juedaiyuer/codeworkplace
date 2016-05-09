public class demo
{
    public static void main(String[] args){
	Factory factory = new Factory();
	Car createCar = factory.getCar("Benz");
	createCar.create();	
    }
}
