// Faculty Data for CST Department, IIEST Shibpur
const facultyList = [
    {
        name: "Dr. Abhik Mukherjee",
        photo: "https://oldwww1926.iiests.ac.in/assets/images/faculty/5dd78d8188470abhikPhoto.jpg",
        email: "abhik@cs.becs.ac.in",
        qualification: "Ph.D. in Computer Science & Technology",
        subjects: ["Design & Analysis of Algorithms", "Advanced Algorithms"],
        research: ["Graph Algorithms", "Combinatorial Optimization", "Theory of Computation"]
    },
    {
        name: "Dr. Amit Biswas",
        photo: "https://oldwww1926.iiests.ac.in/assets/images/faculty/68b02c394777eFormal_Amit_H%20(1).png",
        email: "amitbiswas@cs.iiests.ac.in",
        qualification: "Ph.D. in Computer Science & Engineering",
        subjects: ["Distributed Systems", "Cloud Computing"],
        research: ["Distributed Systems", "Cloud Computing", "Multi-criteria Decision Making (MCDM)", "Blockchain Technology", "Quantum Computing"]
    },
    {
        name: "Dr. Apurba Sarkar",
        photo: "https://oldwww1926.iiests.ac.in/assets/images/faculty/69255e6b3af97510948582_9942185039234381_4863269382280843825_n.jpg",
        email: "sarkar@cs.iiests.ac.in",
        qualification: "Ph.D. in Computer Science & Technology",
        subjects: ["Discrete Mathematics", "Data Structures"],
        research: ["Digital Geometry", "Combinatorial Geometry", "Computational Geometry", "Text Summarization"]
    },
    {
        name: "Dr. Ashish Kumar Layek",
        photo: "https://oldwww1926.iiests.ac.in/assets/images/faculty/ashishlayek_cst.jpg",
        email: "ashish@cs.iiests.ac.in",
        qualification: "Ph.D. in Engineering",
        subjects: ["Computer Networks", "Wireless Communication"],
        research: ["Wireless Telecommunication and Networking", "Pattern Recognition", "Digital Image Processing"]
    },
    {
        name: "Dr. Asit Kumar Das",
        photo: "https://oldwww1926.iiests.ac.in/assets/images/faculty/photo.png",
        email: "akdas@cs.iiests.ac.in",
        qualification: "Ph.D. in Computer Science & Technology",
        subjects: ["Machine Learning", "Data Mining"],
        research: ["Data Mining and Pattern Recognition", "Social Networks", "Bioinformatics", "Soft Computing"]
    },
    {
        name: "Dr. Biplab Kumar Sikdar",
        photo: "https://oldwww1926.iiests.ac.in/assets/images/faculty/cst_bksikdar.jpg",
        email: "biplab@cs.iiests.ac.in",
        qualification: "Ph.D. in Computer Science & Engineering",
        subjects: ["Computer Architecture", "Digital Logic Circuit Design"],
        research: ["Cellular Automata", "Computer Architecture", "VLSI Testing"]
    },
    {
        name: "Dr. Devleena Ghosh",
        photo: "https://oldwww1926.iiests.ac.in/assets/images/faculty/69255d735f6cfWhatsApp%20Image%202025-11-24%20at%2013.13.50_1785e3c6.jpg",
        email: "devleena@cs.iiests.ac.in",
        qualification: "Ph.D. in Computer Science & Engineering",
        subjects: ["Data Structures & Algorithms", "Theory of Computation"],
        research: ["Formal Verification", "Model Checking", "Embedded Systems", "Automata Theory"]
    },
    {
        name: "Dr. Jaya Sil",
        photo: "https://oldwww1926.iiests.ac.in/assets/images/faculty/5de528372c999photo-js.jpeg",
        email: "js@cs.iiests.ac.in",
        qualification: "Ph.D. in Engineering",
        subjects: ["Artificial Intelligence", "Bio-Informatics"],
        research: ["Image Processing", "Computer Vision", "Machine Learning", "Bio-Informatics"]
    },
    {
        name: "Dr. Malay Kule",
        photo: "https://oldwww1926.iiests.ac.in/assets/images/faculty/669e11b61a0261000003808.jpg",
        email: "malay@cs.iiests.ac.in",
        qualification: "Ph.D. in Computer Science & Technology",
        subjects: ["Microprocessors & Microcontrollers", "Digital Systems"],
        research: ["Defect Tolerance & Testing of Nanoscale Circuits", "VLSI Design"]
    },
    {
        name: "Dr. Manas Hira",
        photo: "https://oldwww1926.iiests.ac.in/assets/images/faculty/cst_mhira.jpg",
        email: "manas@cs.iiests.ac.in",
        qualification: "Ph.D. in Computer Science & Engineering",
        subjects: ["Automata Theory & Computability", "Compiler Design"],
        research: ["Theoretical Computer Science", "Formal Languages"]
    },
    {
        name: "Dr. Nirnay Ghosh",
        photo: "https://oldwww1926.iiests.ac.in/assets/images/faculty/5f9a84d7abd0433584458_1755658291192872_6819064364054609920_n.jpg",
        email: "nirnay@cs.iiests.ac.in",
        qualification: "Ph.D. in Computer Science, IIT Kharagpur",
        subjects: ["Distributed Systems", "Cloud Computing"],
        research: ["Information/Network Security", "Mobile Crowdsensing", "Internet of Things (IoT)", "Cloud Security"]
    },
    {
        name: "Dr. Samit Biswas",
        photo: "https://oldwww1926.iiests.ac.in/assets/images/faculty/samit.jpg",
        email: "samit@cs.iiests.ac.in",
        qualification: "Ph.D. in Computer Science & Engineering",
        subjects: ["Object-Oriented Programming", "Graphics & Multimedia"],
        research: ["Digital Image Processing and Analysis", "Computer Graphics"]
    },
    {
        name: "Dr. Sekhar Mandal",
        photo: "https://oldwww1926.iiests.ac.in/assets/images/faculty/sekhar__cst.jpg",
        email: "sekhar@cs.iiests.ac.in",
        qualification: "Ph.D. in Computer Science & Engineering",
        subjects: ["Operating Systems", "Pattern Recognition"],
        research: ["Image Processing", "Pattern Recognition", "Document Processing"]
    },
    {
        name: "Dr. Sipra Das Bit",
        photo: "https://oldwww1926.iiests.ac.in/assets/images/faculty/5e5501ff1f488IMG-20191227-WA0005.jpg",
        email: "sb@cs.iiests.ac.in",
        qualification: "Ph.D. in Computer Science & Engineering",
        subjects: ["Mobile Computing", "Wireless Sensor Networks"],
        research: ["Mobile Computing", "Wireless Sensor Networks", "Delay Tolerant Networks"]
    },
    {
        name: "Dr. Sulata Mitra",
        photo: "https://oldwww1926.iiests.ac.in/assets/images/faculty/61234ce4eaa33IMG_20210823_125033.jpg",
        email: "sulata@cs.iiests.ac.in",
        qualification: "Ph.D. in Computer Science & Engineering",
        subjects: ["Ad-hoc Networks", "Database Management Systems"],
        research: ["Mobile Computing", "QoS Issues in Cellular Networks", "Ad-hoc Networks", "Multihomed Mobile Networks"]
    },
    {
        name: "Dr. Surajeet Ghosh",
        photo: "https://oldwww1926.iiests.ac.in/assets/images/faculty/sjg.png",
        email: "surajeet@cs.iiests.ac.in",
        qualification: "Ph.D. in Computer Science & Technology",
        subjects: ["Computer Organization", "Advanced Computer Architecture"],
        research: ["Computer Architecture", "Hardware Security", "Embedded Systems"]
    },
    {
        name: "Dr. Tamal Pal",
        photo: "https://oldwww1926.iiests.ac.in/assets/images/faculty/5dca99372efa6tamal_pal.jpg",
        email: "tamal@cs.iiests.ac.in",
        qualification: "Ph.D. in Computer Science & Engineering",
        subjects: ["Image Processing", "Multimedia Systems"],
        research: ["Image Processing", "Video Processing", "Multimedia Systems"]
    }
];