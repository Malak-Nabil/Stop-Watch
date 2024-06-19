import java.util.List;
class instructor extends user_creation {
    private String specialization;
    private List<course> courses;

    public instructor(String name, String email, String password, String specialization) {
        super(name, email, password);
        this.specialization = specialization;
    }

    @Override
    public String get_user_type() {
        return "instructor";
    }

    public String get_instructor_specialization() {
        return specialization;
    }

    public void add_course(course course){
        courses.add(course);
    }

    public void enroll_student_directlly(course course,student student){
        course.add_student(student);
    }

    public List<course> courses(){
        return courses;
    }
}
