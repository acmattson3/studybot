import os
import sys

def convert_to_markdown(input_filename):
    # Derive the output filename with .md extension
    output_filename = os.path.splitext(input_filename)[0] + '.md'
    
    # Open the input and output files
    with open(input_filename, 'r') as infile, open(output_filename, 'w') as outfile:
        for line in infile:
            line = line.strip()

            # Turn comments into headers instead of skipping them
            if line.startswith('//'):
                header = line.lstrip('/').strip()
                outfile.write(f'# {header}\n\n')
                continue

            # Split the line into question and answer using " !! " as the delimiter
            if ' !! ' in line:
                question, answer = line.split(' !! ')
                # Replace `\n` in the answer with actual newlines
                answer = answer.replace('\\n', '\n')
                # Write to the output file in Markdown format
                outfile.write(f'### {question.strip()}\n\n')
                outfile.write(f'{answer.strip()}\n\n')

    print(f"Markdown file '{output_filename}' created successfully.")

if __name__ == "__main__":
    # Check if a filename argument was provided
    if len(sys.argv) < 2:
        print("Usage: python studybot_to_markdown.py <filename>")
        sys.exit(1)

    # Get the filename from the command-line arguments
    input_filename = sys.argv[1]

    # Call the function to convert the file
    convert_to_markdown(input_filename)
