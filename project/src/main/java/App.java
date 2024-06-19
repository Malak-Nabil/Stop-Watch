import java.util.List;

public class App {
    public static void main(String[] args) throws Exception {
        instructor instructor_1=new instructor("hussein", "hussein37156@gmail.com", "30788658", "MCT");
        course course_1=new course("ff", instructor_1);

        student student_1=new student("amr", "vbghnj", "ghjفقثk", 15);
        student student_2=new student("amro", "vbhgnj", "ghرjk", 15);
        student student_3=new student("amre", "vbhnmnj", "ghلقjk", 15);
        student student_4=new student("amtre", "vbhnmnj", "ghلقjk", 15);



        student_1.enroll(course_1);
        instructor_1.enroll_student_directlly(course_1,student_2);
        course_1.add_student(student_3);
        course_1.add_student(student_4);


        List<student> coursesEnrolled = course_1.enrolled_students();

        for (int j = 0; j < coursesEnrolled.size(); j++) {
            System.out.println("      " + (j + 1) + ". " + coursesEnrolled.get(j).get_name());
        }

         
        


    }
}