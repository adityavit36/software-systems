import React, { useState ,useEffect} from 'react';
import 'bootstrap/dist/css/bootstrap.min.css'; // Import Bootstrap styles

const StudentForm = () => {
    const [student, setStudent] = useState({
        firstName: '',
        lastName: '',
        email: '',
        graduationYear: '',
        photographPath: '', // Combined with base64
    });

    const [domains, setDomains] = useState([]);
    const [selectedDomainId, setSelectedDomainId] = useState(0);

    useEffect(() => {
        fetch('http://localhost:8080/api/students/domains')
            .then((response) => response.json())
            .then((data) => { setDomains(data); setSelectedDomainId(data[0].domain_Id); })
            .catch((error) => console.error('Error fetching domains:', error));
    }, []);

    const handleChange = (e) => {
        const { name, value, type } = e.target;
        setStudent((prevStudent) => ({
            ...prevStudent,
            [name]: type === 'file' ? e.target.files[0] : value,
        }));
    };

    const handleImageChange = (e) => {
        const file = e.target.files[0];
        if (file) {
            const reader = new FileReader();
            reader.onload = function (event) {
                setStudent((prevStudent) => ({
                    ...prevStudent,
                    photographPath: event.target.result.split(',')[1],
                }));
            };
            reader.readAsDataURL(file);
        }
    };

    const handleSubmit = async (e) => {
        e.preventDefault();
        console.log(selectedDomainId);
        console.log("Form data - ", student);
        try {
            const response = await fetch('http://localhost:8080/api/students/add', {
                method: 'POST',
                body: JSON.stringify({
                    'firstName': student.firstName,
                    'lastName': student.lastName,
                    'email': student.email,
                    'domain': domains.find(d => d.domain_Id == selectedDomainId),
                    'graduationYear': student.graduationYear,
                    'photographPath': student.photographPath, // Include base64 within photographPath
                }),
                headers: {
                    'Content-type': 'application/json;charset=UTF-8'
                }
            });

            if (response.ok) {
                const savedStudent = await response.json();
                console.log('Student added:', savedStudent);
            } else {
                console.error('Failed to add student');
            }
        } catch (error) {
            console.error('Error:', error);
        }
    };

    return (
        <form onSubmit={handleSubmit} className="container mt-4">
            <div className="mb-3">
                <label className="form-label">firstName</label>
                <input type="text" className="form-control" name="firstName" value={student.firstName} onChange={handleChange} />
            </div>
            <div className="mb-3">
                <label className="form-label">lastName</label>
                <input type="text" className="form-control" name="lastName" value={student.lastName} onChange={handleChange} />
            </div>
            <div className="mb-3">
                <label className="form-label">email</label>
                <input type="text" className="form-control" name="email" value={student.email}onChange={handleChange}  />
            </div>
            <div className="mb-3">
                <label className="form-label">graduationYear</label>
                <input type="number" className="form-control" name="graduationYear" value={student.graduationYear}onChange={handleChange}  />
            </div>
            <div className="mb-3">
                <label className="form-label">domain</label>
                <select className="form-select" name="domain" value={selectedDomainId}onChange={e=>setSelectedDomainId(e.target.value)} >
                    {
                        domains.map((d)=>{
                            return (
                                <option key = {d.domain_Id} value = {d.domain_Id}>
                                {d.program+d.batch}
                                </option>);
                        })
                    }
                    {/* <option value="M.Tech CSE">M.Tech CSE</option>
                    <option value="M.Tech ECE">M.Tech ECE</option>
                    <option value="IM.Tech CSE">IMtech CSE</option>
                    <option value="IM.Tech ECE">IMtech ECE</option>
                    <option value="Phd CSE">IMtech CSE</option>
                    <option value="Phd ECE">IMtech ECE</option> */}
                </select>
            </div>
            <div className="mb-3">
                <label className="form-label">Image</label>
                <input type="file" className="form-control" name="image" onChange={handleImageChange} accept="image/*" />
            </div>
            <button type="submit" className="btn btn-primary">
                Submit
            </button>
        </form>
    );
};

export default StudentForm;