public abstract class TemplateBase
{
    public void operationBefore()
    {
	System.out.println("操作前...");
    }
    
    public void operationAfter()
    {
	System.out.println("操作后...");
    }

    public abstract void operation();

    //业务逻辑
    public void logicAction()
    {
	operationBefore();
	operation();
	operationAfter();
    }
}
