import os
import http.server
import socketserver
import urllib.parse

class FileExplorerHandler(http.server.SimpleHTTPRequestHandler):
    def do_GET(self):
        parsed_path = urllib.parse.urlparse(self.path)
        path = parsed_path.path
        
        if path == '/':
            self.send_response(200)
            self.send_header('Content-type', 'text/html')
            self.end_headers()
            
            # Create HTML to show file structure
            html = '<html><head><title>ARMA Reforger Team Management Mod</title></head><body>'
            html += '<h1>ARMA Reforger Team Management Mod File Structure</h1>'
            html += '<h2>Scripts and Files:</h2>'
            
            # Display file structure
            html += self.get_file_structure()
            
            # Display errors and compilation issues
            html += '<h2>Compilation Status:</h2>'
            html += self.get_compilation_status()
            
            html += '</body></html>'
            
            self.wfile.write(html.encode())
        else:
            super().do_GET()
    
    def get_file_structure(self):
        html = '<ul>'
        def add_dir(path, indent=''):
            nonlocal html
            for item in sorted(os.listdir(path)):
                if item.startswith('.'):
                    continue
                    
                full_path = os.path.join(path, item)
                if os.path.isdir(full_path):
                    html += f'<li><strong>{indent}{item}/</strong></li>'
                    html += '<ul>'
                    add_dir(full_path, indent + '&nbsp;&nbsp;')
                    html += '</ul>'
                elif item.endswith('.c'):
                    html += f'<li>{indent}{item}</li>'
            
        try:
            add_dir('.')
        except Exception as e:
            html += f'<li>Error reading directory: {str(e)}</li>'
            
        html += '</ul>'
        return html
    
    def get_compilation_status(self):
        html = '<pre>'
        try:
            for mod_dir in ['Scripts', 'package/Scripts', 'TeamManagement_Release/TeamManagement/Scripts']:
                teamplayercomp_path = f'{mod_dir}/Game/TeamManagement/TeamPlayerComponent.c'
                if os.path.exists(teamplayercomp_path):
                    with open(teamplayercomp_path, 'r') as f:
                        content = f.read()
                        html += f'TeamPlayerComponent in {mod_dir}:\n'
                        for i, line in enumerate(content.split('\n')[:10]):
                            html += f'{i+1}: {line}\n'
                        html += '\n\n'
                        
                teamnetwork_path = f'{mod_dir}/Game/TeamManagement/TeamNetworkComponent.c'
                if os.path.exists(teamnetwork_path):
                    with open(teamnetwork_path, 'r') as f:
                        content = f.read()
                        html += f'TeamNetworkComponent in {mod_dir}:\n'
                        if 'ScriptRPC' in content:
                            html += 'CONTAINS ScriptRPC references!\n'
                        else:
                            html += 'No ScriptRPC references found.\n'
                        html += '\n\n'
        except Exception as e:
            html += f'Error checking compilation: {str(e)}'
            
        html += '</pre>'
        return html

# Set up and run the server
PORT = 5000
Handler = FileExplorerHandler

with socketserver.TCPServer(("", PORT), Handler) as httpd:
    print(f"Serving at port {PORT}")
    httpd.serve_forever()