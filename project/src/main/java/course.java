import java.util.ArrayList;
import java.util.List;

class course {
    private String course_name;
    private instructor instructor;
    private List<student> enrolled_students;

    public course(String course_name, instructor instructor) {
        this.course_name = course_name;
        this.instructor = instructor;
        this.enrolled_students = new ArrayList<>();
    }

    public String get_course_name() {
        return course_name;
    }

    public instructor get_instructor() {
        return instructor;
    }

    public List<student> enrolled_students() {
        return enrolled_students;
    }

    public void add_student(student student) {
        enrolled_students.add(student);
    }

}