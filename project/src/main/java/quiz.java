import java.util.Map;

class quiz {
    
    private int duration;
    private course course;
    private String title;
    private Map<student, String> grade;

    public quiz(int duration,course course,String title){
        this.duration=duration;
        this.course=course;
        this.title=title;
    }

    public void add_grade(student student,String grade){
        (this.grade).put(student, grade);
    }

    public String get_title() {
        return title;
    }

    public int get_duration() {
        return duration;
    }

    public course get_course() {
        return course;
    }

    public Map<student, String> get_grade() {
        return grade;
    }



}
