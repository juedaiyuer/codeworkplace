package test;

import org.hibernate.Session;
import org.hibernate.Transaction;

import util.hibernateUtil;
import entity.Grade;
import entity.Student;


//测试单向多对一(学生--->班级)

public class Test2 {
	public static void main(String[] args) {
		//save();
		findGradeByStudent();
	}
	
	//保存
	public static void save()
	{
		Grade g = new Grade("电气一班", "信息学院");
		Student stu1 = new Student("王九九","女");
		Student stu2 = new Student("林浣溪", "女");
		
		//设置关联关系
		g.getStudents().add(stu1);
		g.getStudents().add(stu2);
		stu1.setGrade(g);
		stu2.setGrade(g);
		
		Session session = new hibernateUtil().getSession();
		Transaction tx = session.beginTransaction();
		session.save(g);
		session.save(stu1);
		session.save(stu2);
		tx.commit();
		hibernateUtil.closeSession(session);
		
	}
	
	//查询学生所在班级信息
	public static void findGradeByStudent()
	{
		Session session = hibernateUtil.getSession();
		Student stu =(Student) session.get(Student.class, 2);
		System.out.println(stu.getSid()+","+stu.getSname()+","+stu.getSex());
		
		Grade g = stu.getGrade();
		System.out.println(g.getGid()+","+g.getGname()+","+g.getGdesc());
		hibernateUtil.closeSession(session);
	}
}
