package com.example.registration.student;
import com.example.registration.credentials.Credentials;
import com.example.registration.credentials.CredentialsRepository;
import com.example.registration.domain.Domain;
import com.example.registration.domain.DomainRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.*;

@Service
public class StudentService {
    private final DomainRepository domainRepository;
    private final StudentRepository studentRepository;
    private final CredentialsRepository credentialsRepository;
    @Autowired
    public StudentService( DomainRepository domainRepository,StudentRepository studentRepository,CredentialsRepository credentialsRepository){
        this.domainRepository = domainRepository;
        this.studentRepository = studentRepository;
        this.credentialsRepository = credentialsRepository;
    }
    public Student saveStudent(Student student) { // Implement the logic to save a student
        if (studentRepository.existsByEmail(student.getEmail())) {
            return null;
        }
        if (student.getFirstName() == null || student.getLastName() == null || student.getPhotographPath() == null) {
            return null;
        }
        if (!isValidEmail(student.getEmail()) || !isValidName(student.getFirstName()) || !isValidName(student.getLastName())) {
            // Handle invalid name (throw an exception, return null, etc.)
            return null;
        }
        // Validate email
        String rollNumber = generateUniqueRollNumber(student.getDomain(),student.getGraduationYear());
        student.setRollNumber(rollNumber);
        Optional<Domain> d = domainRepository.findById(student.getDomain().getDomain_Id());
        if(d.get().getCapacity() <= 0) return null;
        domainRepository.deleteById(student.getDomain().getDomain_Id());
        d.get().setCapacity(d.get().getCapacity()-1);
        domainRepository.save(d.get());
        Optional<Domain> d1 = domainRepository.findById(student.getDomain().getDomain_Id());
        return studentRepository.save(student);
    }
    private boolean isValidName(String name) { // Check if the name contains only alphabets
        return name != null && name.matches("^[a-zA-Z]+$");
    }
    private boolean isValidEmail(String email) { // Check if the email follows the pattern for @gmail.com addresses
        return email != null && email.matches("^[a-zA-Z0-9._%+-]+@gmail\\.com$");
    }
    public Student getStudentById(Long id) { // Implement the logic to retrieve a student by ID
        return studentRepository.findById(id).orElse(null);
    }
    public List<Student> getAllStudents() { // Implement the logic to retrieve all students
        return studentRepository.findAll();
    }
    private String generateUniqueRollNumber(Domain domain, int graduationYear) {
        // Implement your logic to generate a unique roll number based on the domain
        // For demonstration purposes, let's use a simple format
        Dictionary<String, String> dict = new Hashtable<>();
        dict.put("mtech","MT");
        dict.put("imtech","IMT");
        dict.put("ms","MS");
        dict.put("phd","Phd");
        return dict.get(domain.getProgram().toLowerCase())+graduationYear +generateUniqueIdentifier();
    }
    public boolean login(Credentials credentials){
        Optional<Credentials> temp =credentialsRepository.findById(credentials.getUsername());
        return temp.map(value-> value.getPassword().equals(credentials.getPassword())).orElse(false);
    }
    private static String generateUniqueIdentifier() { // Generate a random 3-digit number
        int randomThreeDigitNumber = generateRandomThreeDigitNumber();// Return the 3-digit number as a string
        return String.valueOf(randomThreeDigitNumber);
    }
    private static int generateRandomThreeDigitNumber() {
        // Generate a random 3-digit number
        Random random = new Random();
        return random.nextInt(900) + 100; // Generates a random number between 100 and 999
    } // Implement other service methods as needed
    public List<Domain> getDomains() {
        return domainRepository.findAll();
    }
}