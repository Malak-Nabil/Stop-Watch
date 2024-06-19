
import java.util.ArrayList;
import java.util.List;
class student extends user_creation {

    private int student_age;
    private List<course> enrolled_courses;

    public student(String name, String email, String password, int student_age) {
        super(name, email, password);
        this.student_age = student_age;
        this.enrolled_courses = new ArrayList<>();
    }

    @Override
    public String get_user_type() {
        return "student";
    }

    public int get_student_age() {
        return student_age;
    }

    public void enroll(course course) {
        enrolled_courses.add(course);
        course.add_student(this); 
    }

    public List<course> enrolled_courses() {
        return enrolled_courses;
    }

}