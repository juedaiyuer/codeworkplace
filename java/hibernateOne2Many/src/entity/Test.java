package entity;

import java.util.Set;

import org.hibernate.Session;
import org.hibernate.Transaction;

import util.hibernateUtil;

public class Test {
	public static void main(String[] args) {
		//add();
		//findStudentByGrade();
		//update();
		delete();
	}
	
	//将学生添加到班级
	public static void add()
	{
		Grade g = new Grade("电气一班","信息学院");
		Student stu1 = new Student("依然", "女");
		Student stu2 = new Student("牧月", "女");
		
		//在学生表中添加相应的班级编号,需要在班级中添加学生,建立关联关系
		g.getStudents().add(stu1);
		g.getStudents().add(stu2);
	
		Session session = hibernateUtil.getSession();
		Transaction tx = session.beginTransaction();
		session.save(g);
		session.save(stu1);
		session.save(stu2);
		tx.commit();
		hibernateUtil.closeSession(session);
		
	}
	
	//学生信息的查询,班级中学生信息
	//建立关联关系后,可以方便的从一个对象导航到另一个对象
	//注意关联的方向 班级--->学生
	
	public static void findStudentByGrade()
	{
		Session session = hibernateUtil.getSession();
		Grade grade = (Grade) session.get(Grade.class,1);
		System.out.println(grade.getGname()+","+grade.getGdesc());
		
		Set<Student>  students = grade.getStudents();
		for(Student stu:students)
		{
			System.out.println(stu.getSname()+","+stu.getSex());
		}
		
	}
	
	//修改学生信息
	public static void update()
	{
		Grade g = new Grade("健行一班", "健行学院");
		
		Session  session = hibernateUtil.getSession();
		Transaction tx = session.beginTransaction();
		Student stu = (Student)session.get(Student.class, 1);
		g.getStudents().add(stu);
		session.save(g);
		tx.commit();
		hibernateUtil.closeSession(session);
	}
	
	//删除学生信息
	public static void delete()
	{
		Session session = hibernateUtil.getSession();
		Transaction tx = session.beginTransaction();
		Student stu = (Student)session.get(Student.class, 1);
		session.delete(stu);
		tx.commit();
		hibernateUtil.closeSession(session);
	}
}
