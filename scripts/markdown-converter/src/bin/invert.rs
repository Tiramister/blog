use anyhow::Result;
use regex::Regex;
use std::io::{self, Read};

struct Link {
    label: String,
    url: String,
}

struct FrontMatter {
    title: Option<String>,
    date: Option<String>,
    tags: Vec<String>,
    links: Vec<Link>,
}

impl FrontMatter {
    fn to_string(&self) -> String {
        let mut texts = Vec::new();

        if let Some(title) = &self.title {
            texts.push(format!("# {}", title));
        }
        if let Some(date) = &self.date {
            texts.push(format!("<!--date {}-->", date));
        }
        if !self.tags.is_empty() {
            texts.push(format!("<!--tags {}-->", self.tags.join(" ")));
        }
        if !self.links.is_empty() {
            for link in &self.links {
                texts.push(format!(
                    "<!--link label=\"{}\" url={}-->",
                    link.label, link.url
                ));
            }
        }

        texts.join("\n")
    }
}

fn get_front_matter(text: &mut String) -> String {
    let re = Regex::new(r"(?s)^---\n(.*?)\n---").unwrap();

    let cap_opt = re.captures(text);
    let front_matter = if let Some(cap) = cap_opt {
        cap.get(1).unwrap().as_str().to_string()
    } else {
        "".to_string()
    };

    *text = re.replace(text, "").to_string();

    front_matter
}

fn read_file<R: Read>(reader: &mut R) -> Result<String> {
    let mut buf = String::new();
    reader.read_to_string(&mut buf)?;
    Ok(buf)
}

fn main() -> Result<()> {
    println!("invert to valid markdown style");

    let mut stdin = io::stdin();
    let mut text = read_file(&mut stdin)?;

    let front_matter = get_front_matter(&mut text);
    println!("front matter: \n{}", front_matter);
    println!("~~~~~~~~~~");
    println!("text: \n{}", text);
    println!("~~~~~~~~~~");

    let front_matter = FrontMatter {
        title: Some("test title".to_string()),
        date: Some("2022-09-14".to_string()),
        tags: vec!["atcoder".to_string()],
        links: vec![Link {
            label: "Problem".to_string(),
            url: "https://atcoder.jp/contests/abc001/tasks/abc001_1".to_string(),
        }],
    };

    println!("front matter: \n{}", front_matter.to_string());

    Ok(())
}
