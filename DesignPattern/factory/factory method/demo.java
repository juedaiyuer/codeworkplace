public class demo
{
	public static void main(String[] args){
	BenzFactory factory = new BenzFactory();
	Car createCar = factory.getCar();
	createCar.create();	
	createCar.create();
	}
}
