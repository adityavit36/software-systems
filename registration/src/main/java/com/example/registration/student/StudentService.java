package com.example.registration.student;

import com.example.registration.domain.Domain;
import com.example.registration.domain.DomainRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.List;
import java.util.Random;

@Service
public class StudentService {
    private final DomainRepository domainRepository;
    private final StudentRepository studentRepository;

    @Autowired
    public StudentService( DomainRepository domainRepository,StudentRepository studentRepository) {
        this.domainRepository = domainRepository;
        this.studentRepository = studentRepository;
    }


    public Student saveStudent(Student student) { // Implement the logic to save a student
        String rollNumber = generateUniqueRollNumber(student.getDomain());
        student.setRollNumber(rollNumber); // Save the student to the database
        return studentRepository.save(student);
    }

    public Student getStudentById(Long id) { // Implement the logic to retrieve a student by ID
        return studentRepository.findById(id).orElse(null);
    }

    public List<Student> getAllStudents() { // Implement the logic to retrieve all students
        return studentRepository.findAll();
    }
    private String generateUniqueRollNumber(Domain domain) {
        // Implement your logic to generate a unique roll number based on the domain
        // For demonstration purposes, let's use a simple format
        return domain.getProgram().substring(0, 2).toUpperCase() +
                generateUniqueIdentifier();
    }
    private static String generateUniqueIdentifier() {
        // Generate a random 3-digit number
        int randomThreeDigitNumber = generateRandomThreeDigitNumber();
        // Return the 3-digit number as a string
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