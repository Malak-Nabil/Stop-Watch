
class parents extends user_creation {
    public parents(String name, String email, String password) {
        super(name, email, password);
    }

    @Override
    public String get_user_type() {
        return "parents";
    }



  
}
